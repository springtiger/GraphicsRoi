#ifndef GRAPHICSCHARTITEMLINESEGMENT_H
#define GRAPHICSCHARTITEMLINESEGMENT_H

#include "graphicschartshapeslib_global.h"
#include "graphicsItemLine.h"
#include "interfaceGraphicsChart.h"

class GraphicsChartItemLineSegmentPrivate;
class GRAPHICSCHARTSHAPESLIBSHARED_EXPORT GraphicsChartItemLineSegment : public GraphicsItemLine
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
protected:
    GraphicsChartItemLineSegment(GraphicsChartItemLineSegmentPrivate &dd, QGraphicsObject *parent);
public:
    explicit GraphicsChartItemLineSegment(IGraphicsChart *pInterface, QGraphicsObject *parent = Q_NULLPTR);
    explicit GraphicsChartItemLineSegment(IGraphicsChart *pInterface, const QLineF &valueLine, QGraphicsObject *parent = Q_NULLPTR);
    explicit GraphicsChartItemLineSegment(IGraphicsChart *pInterface, const QPointF &ptValueStart, const QPointF &ptValueStop, QGraphicsObject *parent = Q_NULLPTR);
public:
    void init();
    void setLine(const QLineF &valueLine);
    void setLine(const QPointF &ptValueStart, const QPointF &ptValueStop);
    void setStart(const QPointF &ptValueStart);
    void setStop(const QPointF &ptValueStop);
private:
    Q_DISABLE_COPY(GraphicsChartItemLineSegment)
    Q_DECLARE_PRIVATE_D(QGraphicsItem::d_ptr.data(), GraphicsChartItemLineSegment)
};

#endif // GRAPHICSCHARTITEMLINESEGMENT_H
