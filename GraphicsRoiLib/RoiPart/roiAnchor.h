#ifndef ROIANCHOR_H
#define ROIANCHOR_H

#include "graphicsroilib_global.h"
#include "graphicsItemPoint.h"

namespace GraphicsRoi
{

class RoiAnchorPrivate;
class GRAPHICSROILIBSHARED_EXPORT RoiAnchor : public GraphicsItemPoint
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
protected:
    RoiAnchor(RoiAnchorPrivate &dd, QGraphicsObject *scaleObj, QGraphicsObject *parent);
//public:
//    explicit RoiAnchor(QGraphicsObject *parent = Q_NULLPTR);
//    explicit RoiAnchor(const QPointF& point, const QSizeF& size, ShapeStyle style, QGraphicsObject *parent = Q_NULLPTR);
public:
    enum { Type = Anchor };
    int type() const Q_DECL_OVERRIDE;

protected:
    void init();
protected:
    virtual void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;
private:
    Q_DISABLE_COPY(RoiAnchor)
    Q_DECLARE_PRIVATE_D(QGraphicsItem::d_ptr.data(), RoiAnchor)
};

}
#endif // ROIANCHOR_H
