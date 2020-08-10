#ifndef GRAPHICSCHARTITEMRECTORIENTATION_H
#define GRAPHICSCHARTITEMRECTORIENTATION_H

#include "graphicschartshapeslib_global.h"
#include "graphicsItemRect.h"
#include "interfaceGraphicsChart.h"

class GraphicsChartItemRectOrientationPrivate;
class GRAPHICSCHARTSHAPESLIBSHARED_EXPORT GraphicsChartItemRectOrientation : public GraphicsItemRect
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
protected:
    GraphicsChartItemRectOrientation(GraphicsChartItemRectOrientationPrivate &dd, QGraphicsObject *parent);
public:
    explicit GraphicsChartItemRectOrientation(IGraphicsChart *pInterface, QGraphicsObject *parent = Q_NULLPTR);
    explicit GraphicsChartItemRectOrientation(IGraphicsChart *pInterface, qreal fValueA, qreal fValueB, Qt::Orientation orientation, QGraphicsObject *parent = Q_NULLPTR);
public:
    void init();
    void setRect(qreal fValueA, qreal fValueB, Qt::Orientation orientation);
private:
    Q_DISABLE_COPY(GraphicsChartItemRectOrientation)
    Q_DECLARE_PRIVATE_D(QGraphicsItem::d_ptr.data(), GraphicsChartItemRectOrientation)
};

#endif // GRAPHICSCHARTITEMRECTORIENTATION_H
