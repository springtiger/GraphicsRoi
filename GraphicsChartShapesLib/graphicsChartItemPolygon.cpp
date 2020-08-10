#include "graphicsChartItemPolygon.h"
#include "graphicsChartItemPolygon_p.h"

void GraphicsChartItemPolygonPrivate::updateShapePath() const
{
    Q_ASSERT(m_pChartInterface != 0);
    QChart *pChart = m_pChartInterface->chartView()->chart();
    QXYSeries *pSeries = qobject_cast<QXYSeries *>(m_pChartInterface->currentSeries());

    m_polygon.clear();
    foreach (const QPointF& p, m_valuePolygon) {
        m_polygon.append(pChart->mapToPosition(p, pSeries));
    }

    GraphicsItemPolygonPrivate::updateShapePath();
}

GraphicsChartItemPolygon::GraphicsChartItemPolygon(GraphicsChartItemPolygonPrivate &dd, QGraphicsObject *parent)
    : GraphicsItemPolygon(dd, parent)
{
    init();
}

GraphicsChartItemPolygon::GraphicsChartItemPolygon(IGraphicsChart *pInterface, QGraphicsObject *parent)
    : GraphicsItemPolygon(*new GraphicsChartItemPolygonPrivate(pInterface), parent)
{
    init();
}

GraphicsChartItemPolygon::GraphicsChartItemPolygon(IGraphicsChart *pInterface, const QPolygonF &valuePolygon, QGraphicsObject *parent)
    : GraphicsItemPolygon(*new GraphicsChartItemPolygonPrivate(pInterface), parent)
{
    init();
    setPolygon(valuePolygon);
}

void GraphicsChartItemPolygon::init()
{
    Q_D(GraphicsChartItemPolygon);
    d->m_pChartInterface->init(this);
}

void GraphicsChartItemPolygon::setPolygon(const QPolygonF &valuePolygon)
{
    Q_D(GraphicsChartItemPolygon);
    d->m_valuePolygon = valuePolygon;
    this->updateShape();
}

void GraphicsChartItemPolygon::setTriangle(const QPointF &valueP0, const QPointF &valueP1, const QPointF &valueP2)
{
    QPolygonF valuePolygon;
    valuePolygon << valueP0 << valueP1 << valueP2;
    setPolygon(valuePolygon);
}

