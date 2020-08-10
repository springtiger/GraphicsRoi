#ifndef GRAPHICSPOLYGONITEM_H
#define GRAPHICSPOLYGONITEM_H

#include "graphicsShapeItem.h"
#include "graphicsshapeslib_global.h"
namespace GraphicsShapes
{

class GraphicsItemPolygonPrivate;
class GRAPHICSSHAPESLIBSHARED_EXPORT GraphicsItemPolygon : public GraphicsShapeItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
protected:
    GraphicsItemPolygon(GraphicsItemPolygonPrivate &dd, QGraphicsObject *parent);
public:
    explicit GraphicsItemPolygon(QGraphicsObject *parent = Q_NULLPTR);
    explicit GraphicsItemPolygon(const QPolygonF &polygon, QGraphicsObject *parent = Q_NULLPTR);
    ~GraphicsItemPolygon();

signals:
    void polygonChanged(const QPolygonF& polygon);
public:
    QPolygonF polygon() const;
    void setPolygon(const QPolygonF &polygon);
    virtual void append(const QPointF& p);
    virtual void insert(int i, const QPointF& p);
    virtual void updatePos(int i, const QPointF& p);
    virtual void remove(int i);

    Qt::FillRule fillRule() const;
    void setFillRule(Qt::FillRule rule);

    enum { Type = ShapePolygon };
    virtual int type() const Q_DECL_OVERRIDE;

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR) Q_DECL_OVERRIDE;
private:
    Q_DISABLE_COPY(GraphicsItemPolygon)
    Q_DECLARE_PRIVATE_D(QGraphicsItem::d_ptr.data(), GraphicsItemPolygon)
};
}

#endif // GRAPHICSPOLYGONITEM_H
