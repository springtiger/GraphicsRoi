#ifndef GRAPHICSITEMPOINT_H
#define GRAPHICSITEMPOINT_H

#include "graphicsshapeslib_global.h"
#include "graphicsItemRect.h"

namespace GraphicsShapes
{

class GraphicsItemPointPrivate;
class GRAPHICSSHAPESLIBSHARED_EXPORT GraphicsItemPoint : public GraphicsItemRect
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
public:
    // Anchor图形：矩形/圆/十字
    enum ShapeStyle
    {
        Rectangle,
        Circle,
        Cross
    };
    Q_ENUM(ShapeStyle)
protected:
    GraphicsItemPoint(GraphicsItemPointPrivate &dd, QGraphicsObject *scaleObj, QGraphicsObject *parent);
public:
    explicit GraphicsItemPoint(QGraphicsObject *scaleObj, QGraphicsObject *parent = Q_NULLPTR);
    explicit GraphicsItemPoint(const QPointF& point, const QSizeF& size, ShapeStyle style, QGraphicsObject *scaleObj, QGraphicsObject *parent = Q_NULLPTR);
    ~GraphicsItemPoint();
signals:
    void shapeStyleChanged(ShapeStyle style);
    void posChanged(const QPointF& pos);
    void sizeChanged(const QSizeF& size);
public:
    void setPoint(const QPointF& point, const QSizeF& size, ShapeStyle style, bool update = true);
    void setShapeStyle(ShapeStyle style, bool update = true);
    void setPos(const QPointF &pos, bool update = true);
    void setSize(const QSizeF &size, bool update = true);

    ShapeStyle shapeStyle();
    QPointF position();
    QSizeF size();

    enum { Type = ShapePoint };
    virtual int type() const Q_DECL_OVERRIDE;

protected:
    void init(QGraphicsObject *scaleObj);
protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR) Q_DECL_OVERRIDE;
private:
    Q_DISABLE_COPY(GraphicsItemPoint)
    Q_DECLARE_PRIVATE_D(QGraphicsItem::d_ptr.data(), GraphicsItemPoint)
};

}
#endif // GRAPHICSITEMPOINT_H
