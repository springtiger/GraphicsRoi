#ifndef GRAPHICSCHARTITEMLINE_H
#define GRAPHICSCHARTITEMLINE_H

#include "graphicschartshapeslib_global.h"
#include "graphicsItemLine.h"
#include "interfaceGraphicsChart.h"

class GraphicsChartItemLinePrivate;
class GRAPHICSCHARTSHAPESLIBSHARED_EXPORT GraphicsChartItemLine : public GraphicsItemLine
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
protected:
    GraphicsChartItemLine(GraphicsChartItemLinePrivate &dd, QGraphicsObject *parent);
public:
    explicit GraphicsChartItemLine(IGraphicsChart *pInterface, QGraphicsObject *parent = Q_NULLPTR);
    explicit GraphicsChartItemLine(IGraphicsChart *pInterface, qreal fValueA, qreal fValueB, qreal fValueC, QGraphicsObject *parent = Q_NULLPTR);
public:
    void init();
    void setLine(qreal fValueA, qreal fValueB, qreal fValueC);
private:
    Q_DISABLE_COPY(GraphicsChartItemLine)
    Q_DECLARE_PRIVATE_D(QGraphicsItem::d_ptr.data(), GraphicsChartItemLine)
};

#endif // GRAPHICSCHARTITEMLINE_H
