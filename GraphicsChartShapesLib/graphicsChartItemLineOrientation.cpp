#include "graphicsChartItemLineOrientation.h"
#include "graphicsChartItemLineOrientation_p.h"



void GraphicsChartItemLineOrientationPrivate::updateShapePath() const
{
    Q_ASSERT(m_pChartInterface != 0);
    QChart *pChart = m_pChartInterface->chartView()->chart();
    QXYSeries *pSeries = qobject_cast<QXYSeries *>(m_pChartInterface->currentSeries());
    QValueAxis *pAxisX = qobject_cast<QValueAxis *>(pChart->axisX(pSeries));
    QValueAxis *pAxisY = qobject_cast<QValueAxis *>(pChart->axisY(pSeries));

    QPointF valueStart = m_orientation == Qt::Vertical ? QPointF(m_fValue, pAxisY->min()) : QPointF(pAxisX->min(), m_fValue);
    QPointF valueStop  = m_orientation == Qt::Vertical ? QPointF(m_fValue, pAxisY->max()) : QPointF(pAxisX->max(), m_fValue);

    m_line.setP1(pChart->mapToPosition(valueStart, pSeries));
    m_line.setP2(pChart->mapToPosition(valueStop, pSeries));

    GraphicsItemLinePrivate::updateShapePath();

}

GraphicsChartItemLineOrientation::GraphicsChartItemLineOrientation(GraphicsChartItemLineOrientationPrivate &dd, QGraphicsObject *parent)
    : GraphicsItemLine(dd, parent)
{
    init();
}

GraphicsChartItemLineOrientation::GraphicsChartItemLineOrientation(IGraphicsChart *pInterface, QGraphicsObject *parent)
    : GraphicsItemLine(*new GraphicsChartItemLineOrientationPrivate(pInterface), parent)
{
    init();
}

GraphicsChartItemLineOrientation::GraphicsChartItemLineOrientation(IGraphicsChart *pInterface, qreal fValue, Qt::Orientation orientation, QGraphicsObject *parent)
    : GraphicsItemLine(*new GraphicsChartItemLineOrientationPrivate(pInterface), parent)
{
    init();
    setLine(fValue, orientation);
}

void GraphicsChartItemLineOrientation::init()
{
    Q_D(GraphicsChartItemLineOrientation);
    d->m_pChartInterface->init(this);
}

void GraphicsChartItemLineOrientation::setLine(qreal fValue, Qt::Orientation orientation)
{
    Q_D(GraphicsChartItemLineOrientation);
    d->m_fValue = fValue;
    d->m_orientation = orientation;

    this->updateShape();
}

void GraphicsChartItemLineOrientation::setValue(qreal fValue)
{
    Q_D(GraphicsChartItemLineOrientation);
    d->m_fValue = fValue;

    this->updateShape();
}

void GraphicsChartItemLineOrientation::setOrientation(Qt::Orientation orientation)
{
    Q_D(GraphicsChartItemLineOrientation);
    d->m_orientation = orientation;

    this->updateShape();
}

