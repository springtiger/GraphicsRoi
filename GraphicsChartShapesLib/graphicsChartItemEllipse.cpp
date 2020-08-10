#include "graphicsChartItemEllipse.h"
#include "graphicsChartItemEllipse_p.h"

#include <QChart>
#include <QValueAxis>

#include <QDebug>

void GraphicsChartItemEllipsePrivate::updateShapePath() const
{
    Q_ASSERT(m_pChartInterface != 0);
    QChart *pChart = m_pChartInterface->chartView()->chart();
    QXYSeries *pSeries = qobject_cast<QXYSeries *>(m_pChartInterface->currentSeries());

    m_rect = QRectF(pChart->mapToPosition(m_valueRect.topLeft(), pSeries), pChart->mapToPosition(m_valueRect.bottomRight(), pSeries));

    GraphicsItemEllipsePrivate::updateShapePath();
}

GraphicsChartItemEllipse::GraphicsChartItemEllipse(GraphicsChartItemEllipsePrivate &dd, QGraphicsObject *parent)
    : GraphicsItemEllipse(dd, parent)
{
    init();
}

GraphicsChartItemEllipse::GraphicsChartItemEllipse(IGraphicsChart *pInterface, QGraphicsObject *parent)
    : GraphicsItemEllipse(*new GraphicsChartItemEllipsePrivate(pInterface), parent)
{
    init();
}

GraphicsChartItemEllipse::GraphicsChartItemEllipse(IGraphicsChart *pInterface, const QPointF &ptValueCenter, const QSizeF &szValueSize, QGraphicsObject *parent)
    : GraphicsItemEllipse(*new GraphicsChartItemEllipsePrivate(pInterface), parent)
{
    setEllepse(ptValueCenter, szValueSize);
    init();
}

void GraphicsChartItemEllipse::init()
{
    Q_D(GraphicsChartItemEllipse);
    d->m_pChartInterface->init(this);
}


void GraphicsChartItemEllipse::setEllepse(const QRectF &valueRect)
{
    Q_D(GraphicsChartItemEllipse);

    d->m_valueRect = valueRect;

    this->updateShape();
}

void GraphicsChartItemEllipse::setEllepse(const QPointF &valueCenter, const QSizeF &valueSize)
{
    Q_D(GraphicsChartItemEllipse);

    d->m_valueRect.setSize(valueSize);
    d->m_valueRect.moveCenter(valueCenter);

    this->updateShape();
}

void GraphicsChartItemEllipse::setCenter(const QPointF &valueCenter)
{
    Q_D(GraphicsChartItemEllipse);

    d->m_valueRect.moveCenter(valueCenter);

    this->updateShape();
}

void GraphicsChartItemEllipse::setSize(const QSizeF &valueSize)
{
    Q_D(GraphicsChartItemEllipse);

    QPointF valueCenter = d->m_valueRect.center();
    d->m_valueRect.setSize(valueSize);
    d->m_valueRect.moveCenter(valueCenter);

    this->updateShape();
}

void GraphicsChartItemEllipse::setRadii(qreal radiusX, qreal radiusY)
{
    setSize(QSizeF(radiusX*2, radiusY*2));
}

QPointF GraphicsChartItemEllipse::centerValue() const
{
    Q_D(const GraphicsChartItemEllipse);
    return d->m_valueRect.center();
}

QSizeF GraphicsChartItemEllipse::sizeValue() const
{
    Q_D(const GraphicsChartItemEllipse);
    return d->m_valueRect.size();
}
