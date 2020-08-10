#include "graphicsChartItemRectOrientation.h"
#include "graphicsChartItemRectOrientation_p.h"


void GraphicsChartItemRectOrientationPrivate::updateShapePath() const
{
    Q_ASSERT(m_pChartInterface != 0);
    QChart *pChart = m_pChartInterface->chartView()->chart();
    QXYSeries *pSeries = qobject_cast<QXYSeries *>(m_pChartInterface->currentSeries());
    QValueAxis *pAxisX = qobject_cast<QValueAxis *>(pChart->axisX(pSeries));
    QValueAxis *pAxisY = qobject_cast<QValueAxis *>(pChart->axisY(pSeries));

    qreal valueMin = qMin(m_fValueA, m_fValueB);
    qreal valueMax = qMax(m_fValueA, m_fValueB);
    QPointF topLeft =     m_orientation == Qt::Vertical ? QPointF(valueMin, pAxisY->min()) : QPointF(pAxisX->min(), valueMin);
    QPointF bottomRight = m_orientation == Qt::Vertical ? QPointF(valueMax, pAxisY->max()) : QPointF(pAxisX->max(), valueMax);

    QRectF rect(topLeft, bottomRight);

    m_rect = QRectF(pChart->mapToPosition(rect.topLeft(), pSeries), pChart->mapToPosition(rect.bottomRight(), pSeries));
    m_rect = m_rect.normalized();

    GraphicsItemRectPrivate::updateShapePath();
}

GraphicsChartItemRectOrientation::GraphicsChartItemRectOrientation(GraphicsChartItemRectOrientationPrivate &dd, QGraphicsObject *parent)
    : GraphicsItemRect(dd, parent)
{
    init();
}

GraphicsChartItemRectOrientation::GraphicsChartItemRectOrientation(IGraphicsChart *pInterface, QGraphicsObject *parent)
    : GraphicsItemRect(*new GraphicsChartItemRectOrientationPrivate(pInterface), parent)
{
    init();
}

GraphicsChartItemRectOrientation::GraphicsChartItemRectOrientation(IGraphicsChart *pInterface, qreal fValueA, qreal fValueB, Qt::Orientation orientation, QGraphicsObject *parent)
    : GraphicsItemRect(*new GraphicsChartItemRectOrientationPrivate(pInterface), parent)
{
    init();
    setRect(fValueA, fValueB, orientation);
}

void GraphicsChartItemRectOrientation::init()
{
    Q_D(GraphicsChartItemRectOrientation);
    d->m_pChartInterface->init(this);
}

void GraphicsChartItemRectOrientation::setRect(qreal fValueA, qreal fValueB, Qt::Orientation orientation)
{
    Q_D(GraphicsChartItemRectOrientation);
    d->m_fValueA = fValueA;
    d->m_fValueB = fValueB;
    d->m_orientation = orientation;

    this->updateShape();
}

