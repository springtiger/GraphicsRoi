#ifndef GRAPHICSCHARTITEMLINEORIENTATION_H
#define GRAPHICSCHARTITEMLINEORIENTATION_H

#include "graphicschartshapeslib_global.h"
#include "graphicsItemLine.h"
#include "interfaceGraphicsChart.h"

class GraphicsChartItemLineOrientationPrivate;
class GRAPHICSCHARTSHAPESLIBSHARED_EXPORT GraphicsChartItemLineOrientation : public GraphicsItemLine
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
protected:
    GraphicsChartItemLineOrientation(GraphicsChartItemLineOrientationPrivate &dd, QGraphicsObject *parent);
public:
    explicit GraphicsChartItemLineOrientation(IGraphicsChart *pInterface, QGraphicsObject *parent = Q_NULLPTR);
    explicit GraphicsChartItemLineOrientation(IGraphicsChart *pInterface, qreal fValue, Qt::Orientation orientation, QGraphicsObject *parent = Q_NULLPTR);
public:
    void init();
    void setLine(qreal fValue, Qt::Orientation orientation);
    void setValue(qreal fValue);
    void setOrientation(Qt::Orientation orientation);
private:
    Q_DISABLE_COPY(GraphicsChartItemLineOrientation)
    Q_DECLARE_PRIVATE_D(QGraphicsItem::d_ptr.data(), GraphicsChartItemLineOrientation)
};

#endif // GRAPHICSCHARTITEMLINEORIENTATION_H
