#include "graphicsChartItemLine.h"
#include "graphicsChartItemLine_p.h"



void GraphicsChartItemLinePrivate::updateShapePath() const
{
    Q_ASSERT(m_pChartInterface != 0);
    QChart *pChart = m_pChartInterface->chartView()->chart();
    QXYSeries *pSeries = qobject_cast<QXYSeries *>(m_pChartInterface->currentSeries());
    QValueAxis *pAxisX = qobject_cast<QValueAxis *>(pChart->axisX(pSeries));
    QValueAxis *pAxisY = qobject_cast<QValueAxis *>(pChart->axisY(pSeries));

    qreal xMin = pAxisX->min();
    qreal xMax = pAxisX->max();
    qreal yMin = pAxisY->min();
    qreal yMax = pAxisY->max();

    QPointF valueStart;
    QPointF valueStop;

    if (m_fValueA == 0)
    { // ax + by + c = 0
        //y = -m_fValueC / m_fValueB;
    }
    else if (m_fValueB == 0)
    {
        //x = -m_fValueC / m_fValueA;
    }
    else
    {

    }
    m_line.setPoints(valueStart, valueStop);

    GraphicsItemLinePrivate::updateShapePath();
}


GraphicsChartItemLine::GraphicsChartItemLine(GraphicsChartItemLinePrivate &dd, QGraphicsObject *parent)
    : GraphicsItemLine(dd, parent)
{
    init();
}

GraphicsChartItemLine::GraphicsChartItemLine(IGraphicsChart *pInterface, QGraphicsObject *parent)
    : GraphicsItemLine(*new GraphicsChartItemLinePrivate(pInterface), parent)
{
    init();
}

GraphicsChartItemLine::GraphicsChartItemLine(IGraphicsChart *pInterface, qreal fValueA, qreal fValueB, qreal fValueC, QGraphicsObject *parent)
    : GraphicsItemLine(*new GraphicsChartItemLinePrivate(pInterface), parent)
{
    init();
}

void GraphicsChartItemLine::init()
{
    Q_D(GraphicsChartItemLine);
    d->m_pChartInterface->init(this);
}

void GraphicsChartItemLine::setLine(qreal fValueA, qreal fValueB, qreal fValueC)
{
    Q_D(GraphicsChartItemLine);
    d->m_fValueA = fValueA;
    d->m_fValueB = fValueB;
    d->m_fValueC = fValueC;

    this->updateShape();
}




