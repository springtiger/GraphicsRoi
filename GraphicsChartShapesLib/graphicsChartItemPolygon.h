#ifndef GRAPHICSCHARTITEMPOLYGON_H
#define GRAPHICSCHARTITEMPOLYGON_H

#include "graphicschartshapeslib_global.h"
#include "graphicsItemPolygon.h"
#include "interfaceGraphicsChart.h"

class GraphicsChartItemPolygonPrivate;
class GRAPHICSCHARTSHAPESLIBSHARED_EXPORT GraphicsChartItemPolygon : public GraphicsItemPolygon
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
protected:
    GraphicsChartItemPolygon(GraphicsChartItemPolygonPrivate &dd, QGraphicsObject *parent);
public:
    explicit GraphicsChartItemPolygon(IGraphicsChart *pInterface, QGraphicsObject *parent = Q_NULLPTR);
    explicit GraphicsChartItemPolygon(IGraphicsChart *pInterface, const QPolygonF& valuePolygon, QGraphicsObject *parent = Q_NULLPTR);
public:
    void init();
    void setPolygon(const QPolygonF &valuePolygon);
    void setTriangle(const QPointF& valueP0, const QPointF& valueP1, const QPointF& valueP2);

private:
    Q_DISABLE_COPY(GraphicsChartItemPolygon)
    Q_DECLARE_PRIVATE_D(QGraphicsItem::d_ptr.data(), GraphicsChartItemPolygon)
};

#endif // GRAPHICSCHARTITEMPOLYGON_H
