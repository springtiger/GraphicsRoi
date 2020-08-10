#ifndef GRAPHICSPOLYLINE_H
#define GRAPHICSPOLYLINE_H

#include "graphicsroilib_global.h"
#include "graphicsItemLine.h"
#include <QGraphicsDropShadowEffect>

class GraphicsPolyLinePrivate;
class GRAPHICSROILIBSHARED_EXPORT GraphicsPolyLine : public GraphicsItemLine
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
protected:
    GraphicsPolyLine(GraphicsPolyLinePrivate &dd, QGraphicsObject *parent);
public:
    explicit GraphicsPolyLine(QGraphicsObject *parent = Q_NULLPTR);
    explicit GraphicsPolyLine(const QLineF &line, QGraphicsObject *parent = Q_NULLPTR);
    explicit GraphicsPolyLine(qreal x1, qreal y1, qreal x2, qreal y2, QGraphicsObject *parent = Q_NULLPTR);
public:
    void setP1(const QPointF& p);
    void setP2(const QPointF& p);
    void setLine(const QLineF &line);

protected:
    void init();
    void updateCursor();
protected:    
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
private:
    Q_DISABLE_COPY(GraphicsPolyLine)
    Q_DECLARE_PRIVATE_D(QGraphicsItem::d_ptr.data(), GraphicsPolyLine)
};

#endif // GRAPHICSPOLYLINE_H
