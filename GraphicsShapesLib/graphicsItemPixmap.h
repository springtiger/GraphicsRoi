#ifndef GRAPHICSPIXMAPITEM_H
#define GRAPHICSPIXMAPITEM_H
#include "graphicsshapeslib_global.h"
#include <QGraphicsObject>
#include "graphicsShapeItem.h"

namespace GraphicsShapes
{

class GraphicsItemPixmapPrivate;
class GRAPHICSSHAPESLIBSHARED_EXPORT GraphicsItemPixmap : public QGraphicsObject
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
protected:
    GraphicsItemPixmap(GraphicsItemPixmapPrivate &dd, QGraphicsObject *parent);
public:
    enum ShapeMode {
        MaskShape,
        BoundingRectShape,
        HeuristicMaskShape
    };

    explicit GraphicsItemPixmap(QGraphicsObject *parent = Q_NULLPTR);
    explicit GraphicsItemPixmap(const QPixmap &pixmap, QGraphicsObject *parent = Q_NULLPTR);
    ~GraphicsItemPixmap();
signals:
    void pixmapChanged(const QPixmap& pixmap);
public:
    QPixmap pixmap() const;
    void setPixmap(const QPixmap &pixmap);

    Qt::TransformationMode transformationMode() const;
    void setTransformationMode(Qt::TransformationMode mode);

    QPointF offset() const;
    void setOffset(const QPointF &offset);
    inline void setOffset(qreal x, qreal y);

    QRectF boundingRect() const Q_DECL_OVERRIDE;
    QPainterPath shape() const Q_DECL_OVERRIDE;
    bool contains(const QPointF &point) const Q_DECL_OVERRIDE;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;

    bool isObscuredBy(const QGraphicsItem *item) const Q_DECL_OVERRIDE;
    QPainterPath opaqueArea() const Q_DECL_OVERRIDE;

    enum { Type = ShapePixmap };
    virtual int type() const Q_DECL_OVERRIDE;

    ShapeMode shapeMode() const;
    void setShapeMode(ShapeMode mode);

protected:
    bool supportsExtension(Extension extension) const Q_DECL_OVERRIDE;
    void setExtension(Extension extension, const QVariant &variant) Q_DECL_OVERRIDE;
    QVariant extension(const QVariant &variant) const Q_DECL_OVERRIDE;
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;

private:
    Q_DISABLE_COPY(GraphicsItemPixmap)
    Q_DECLARE_PRIVATE_D(QGraphicsItem::d_ptr.data(), GraphicsItemPixmap)
};

inline void GraphicsItemPixmap::setOffset(qreal ax, qreal ay)
{ setOffset(QPointF(ax, ay)); }

}
#endif // GRAPHICSPIXMAPITEM_H
