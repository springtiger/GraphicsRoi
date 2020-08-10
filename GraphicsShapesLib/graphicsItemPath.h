#ifndef GRAPHICSPATHITEM_H
#define GRAPHICSPATHITEM_H

#include "graphicsShapeItem.h"
#include "graphicsshapeslib_global.h"

namespace GraphicsShapes
{

class GraphicsItemPathPrivate;
class GRAPHICSSHAPESLIBSHARED_EXPORT GraphicsItemPath : public GraphicsShapeItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
protected:
    GraphicsItemPath(GraphicsItemPathPrivate &dd, QGraphicsObject *parent);
public:
    explicit GraphicsItemPath(QGraphicsObject *parent = Q_NULLPTR);
    explicit GraphicsItemPath(const QPainterPath &path, QGraphicsObject *parent = Q_NULLPTR);
    ~GraphicsItemPath();

signals:
    void pathChanged(const QPainterPath& path);
public:
    QPainterPath path() const;
    void setPath(const QPainterPath &path, bool update = true);

    enum { Type = ShapePath };
    virtual int type() const Q_DECL_OVERRIDE;

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR) Q_DECL_OVERRIDE;
private:
    Q_DISABLE_COPY(GraphicsItemPath)
    Q_DECLARE_PRIVATE_D(QGraphicsItem::d_ptr.data(), GraphicsItemPath)
};
}

#endif // GRAPHICSPATHITEM_H
