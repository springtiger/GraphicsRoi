#ifndef GRAPHICSSHAPEITEM_H
#define GRAPHICSSHAPEITEM_H

#include <QGraphicsObject>
#include <QPainterPath>
#include <QPainter>
#include <QStyleOptionGraphicsItem>

#include "graphicsshapeslib_global.h"

namespace GraphicsShapes
{

class GraphicsShapeItemPrivate;
class GRAPHICSSHAPESLIBSHARED_EXPORT GraphicsShapeItem : public QGraphicsObject
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
protected:
    GraphicsShapeItem(GraphicsShapeItemPrivate &dd, QGraphicsObject *parent);
signals:
    void shapeChanged() const;
public:
    QPen pen() const;
    void setPen(const QPen &pen, bool update = true);

    QBrush brush() const;
    void setBrush(const QBrush &brush);
    // 设置边框颜色
    void setPenColor(const QColor& c);
    // 设置填充颜色
    void setBrushColor(const QColor& color);
    // 设置线宽是否单像素
    void setCosmetic(bool b);

    QRectF boundingRect() const Q_DECL_OVERRIDE;
    QPainterPath shape() const Q_DECL_OVERRIDE;
    bool isObscuredBy(const QGraphicsItem *item) const Q_DECL_OVERRIDE;
    QPainterPath opaqueArea() const Q_DECL_OVERRIDE;
public:
    static QPainterPath qt_graphicsItem_shapeFromPath(const QGraphicsItem *item, const QPainterPath &path, const QPen &pen);
    static void qt_graphicsItem_highlightSelected(QGraphicsItem *item, QPainter *painter, const QStyleOptionGraphicsItem *option);
public slots:
    void updateShape();
protected:

private:
    Q_DISABLE_COPY(GraphicsShapeItem)
    Q_DECLARE_PRIVATE_D(QGraphicsItem::d_ptr.data(), GraphicsShapeItem)
};

}

#endif // GRAPHICSSHAPEITEM_H
