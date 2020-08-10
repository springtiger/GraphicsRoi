#include "graphicsChartItemLineSegment.h"
#include "graphicsChartItemLineSegment_p.h"

#include <QChart>
#include <QValueAxis>

void GraphicsChartItemLineSegmentPrivate::updateShapePath() const
{
    Q_ASSERT(m_pChartInterface != 0);
    QChart *pChart = m_pChartInterface->chartView()->chart();
    QXYSeries *pSeries = qobject_cast<QXYSeries *>(m_pChartInterface->currentSeries());

    m_line.setP1(pChart->mapToPosition(m_valueLine.p1(), pSeries));
    m_line.setP2(pChart->mapToPosition(m_valueLine.p2(), pSeries));

    GraphicsItemLinePrivate::updateShapePath();
}


GraphicsChartItemLineSegment::GraphicsChartItemLineSegment(GraphicsChartItemLineSegmentPrivate &dd, QGraphicsObject *parent)
    : GraphicsItemLine(dd, parent)
{
    init();
}

GraphicsChartItemLineSegment::GraphicsChartItemLineSegment(IGraphicsChart *pInterface, QGraphicsObject *parent)
    : GraphicsItemLine(*new GraphicsChartItemLineSegmentPrivate(pInterface), parent)
{
    init();
}

GraphicsChartItemLineSegment::GraphicsChartItemLineSegment(IGraphicsChart *pInterface, const QLineF &valueLine, QGraphicsObject *parent)
    : GraphicsItemLine(*new GraphicsChartItemLineSegmentPrivate(pInterface), parent)
{
    init();
    setLine(valueLine);
}

GraphicsChartItemLineSegment::GraphicsChartItemLineSegment(IGraphicsChart *pInterface, const QPointF &ptValueStart, const QPointF &ptValueStop, QGraphicsObject *parent)
    : GraphicsItemLine(*new GraphicsChartItemLineSegmentPrivate(pInterface), parent)
{
    init();
    setLine(ptValueStart, ptValueStop);
}

void GraphicsChartItemLineSegment::init()
{
    Q_D(GraphicsChartItemLineSegment);
    d->m_pChartInterface->init(this);
}

void GraphicsChartItemLineSegment::setLine(const QLineF &valueLine)
{
    Q_D(GraphicsChartItemLineSegment);
    d->m_valueLine = valueLine;
    this->updateShape();
}

void GraphicsChartItemLineSegment::setLine(const QPointF &ptValueStart, const QPointF &ptValueStop)
{
    Q_D(GraphicsChartItemLineSegment);
    d->m_valueLine = QLineF(ptValueStart, ptValueStop);
    this->updateShape();
}

void GraphicsChartItemLineSegment::setStart(const QPointF &ptValueStart)
{
    Q_D(GraphicsChartItemLineSegment);
    d->m_valueLine.setP1(ptValueStart);
    this->updateShape();
}

void GraphicsChartItemLineSegment::setStop(const QPointF &ptValueStop)
{
    Q_D(GraphicsChartItemLineSegment);
    d->m_valueLine.setP1(ptValueStop);
    this->updateShape();
}
