#ifndef GRAPHICSRECTITEM_H
#define GRAPHICSRECTITEM_H

#include "graphicsshapeslib_global.h"
#include "graphicsShapeItem.h"

namespace GraphicsShapes
{

class GraphicsItemRectPrivate;
class GRAPHICSSHAPESLIBSHARED_EXPORT GraphicsItemRect : public GraphicsShapeItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
protected:
    GraphicsItemRect(GraphicsItemRectPrivate &dd, QGraphicsObject *parent);
public:
    explicit GraphicsItemRect(QGraphicsObject *parent = Q_NULLPTR);
    explicit GraphicsItemRect(const QRectF &rect, QGraphicsObject *parent = Q_NULLPTR);
    explicit GraphicsItemRect(qreal x, qreal y, qreal w, qreal h, QGraphicsObject *parent = Q_NULLPTR);
    ~GraphicsItemRect();
signals:
    void rectChanged(const QRectF& r);
public:
    QRectF rect() const;
    void setRect(const QRectF &rect, bool update = true);
    inline void setRect(qreal x, qreal y, qreal w, qreal h, bool update = true)
    {
        setRect(QRectF(x, y, w, h), update);
    }


    enum { Type = ShapeRect };
    virtual int type() const Q_DECL_OVERRIDE;

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR) Q_DECL_OVERRIDE;
private:
    Q_DISABLE_COPY(GraphicsItemRect)
    Q_DECLARE_PRIVATE_D(QGraphicsItem::d_ptr.data(), GraphicsItemRect)
};

}
#endif // GRAPHICSRECTITEM_H
