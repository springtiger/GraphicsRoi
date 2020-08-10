#ifndef GRAPHICSCHARTITEMRECT_H
#define GRAPHICSCHARTITEMRECT_H

#include "graphicschartshapeslib_global.h"
#include "graphicsItemRect.h"
#include "interfaceGraphicsChart.h"

class GraphicsChartItemRectPrivate;
class GRAPHICSCHARTSHAPESLIBSHARED_EXPORT GraphicsChartItemRect : public GraphicsItemRect
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
protected:
    GraphicsChartItemRect(GraphicsChartItemRectPrivate &dd, QGraphicsObject *parent);
public:
    explicit GraphicsChartItemRect(IGraphicsChart *pInterface, QGraphicsObject *parent = Q_NULLPTR);
    explicit GraphicsChartItemRect(IGraphicsChart *pInterface, const QRectF &rectValue, QGraphicsObject *parent = Q_NULLPTR);
public:
    void init();
    void setRect(const QRectF &rectValue);
private:
    Q_DISABLE_COPY(GraphicsChartItemRect)
    Q_DECLARE_PRIVATE_D(QGraphicsItem::d_ptr.data(), GraphicsChartItemRect)
};

#endif // GRAPHICSCHARTITEMRECT_H
