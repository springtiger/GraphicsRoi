#include "graphicsChartItemRect.h"
#include "graphicsChartItemRect_p.h"


void GraphicsChartItemRectPrivate::updateShapePath() const
{
    Q_ASSERT(m_pChartInterface != 0);
    QChart *pChart = m_pChartInterface->chartView()->chart();
    QXYSeries *pSeries = qobject_cast<QXYSeries *>(m_pChartInterface->currentSeries());

    m_rect = QRectF(pChart->mapToPosition(m_rectValue.topLeft(), pSeries), pChart->mapToPosition(m_rectValue.bottomRight(), pSeries));

    GraphicsItemRectPrivate::updateShapePath();
}


GraphicsChartItemRect::GraphicsChartItemRect(GraphicsChartItemRectPrivate &dd, QGraphicsObject *parent)
    : GraphicsItemRect(dd, parent)
{
    init();
}

GraphicsChartItemRect::GraphicsChartItemRect(IGraphicsChart *pInterface, QGraphicsObject *parent)
    : GraphicsItemRect(*new GraphicsChartItemRectPrivate(pInterface), parent)
{
    init();
}

GraphicsChartItemRect::GraphicsChartItemRect(IGraphicsChart *pInterface, const QRectF &rectValue, QGraphicsObject *parent)
    : GraphicsItemRect(*new GraphicsChartItemRectPrivate(pInterface), parent)
{
    init();
    setRect(rectValue);
}

void GraphicsChartItemRect::init()
{
    Q_D(GraphicsChartItemRect);
    d->m_pChartInterface->init(this);
}

void GraphicsChartItemRect::setRect(const QRectF &rectValue)
{
    Q_D(GraphicsChartItemRect);
    d->m_rectValue = rectValue;
    d->m_rectValue = d->m_rectValue.normalized();
    this->updateShape();
}

