#ifndef GRAPHICSCHARTITEMELLIPSE_H
#define GRAPHICSCHARTITEMELLIPSE_H

#include "graphicschartshapeslib_global.h"
#include "graphicsItemEllipse.h"

#include "interfaceGraphicsChart.h"

class GraphicsChartItemEllipsePrivate;
class GRAPHICSCHARTSHAPESLIBSHARED_EXPORT GraphicsChartItemEllipse : public GraphicsItemEllipse
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
protected:
    GraphicsChartItemEllipse(GraphicsChartItemEllipsePrivate &dd, QGraphicsObject *parent);
public:
    explicit GraphicsChartItemEllipse(IGraphicsChart *pInterface, QGraphicsObject *parent = Q_NULLPTR);
    explicit GraphicsChartItemEllipse(IGraphicsChart *pInterface, const QPointF &ptValueCenter, const QSizeF &szValueSize, QGraphicsObject *parent = Q_NULLPTR);
public:
    void init();
    void setEllepse(const QRectF &valueRect);
    void setEllepse(const QPointF &valueCenter, const QSizeF &valueSize);
    void setCenter(const QPointF &valueCenter);
    //The center is not moved.
    void setSize(const QSizeF &valueSize);
    void setRadii(qreal radiusX, qreal radiusY);
    QPointF centerValue() const;
    QSizeF sizeValue() const;
private:
    Q_DISABLE_COPY(GraphicsChartItemEllipse)
    Q_DECLARE_PRIVATE_D(QGraphicsItem::d_ptr.data(), GraphicsChartItemEllipse)
};

#endif // GRAPHICSCHARTITEMELLIPSE_H
