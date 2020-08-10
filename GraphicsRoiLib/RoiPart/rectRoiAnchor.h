#ifndef RECTROIANCHOR_H
#define RECTROIANCHOR_H

#include "graphicsroilib_global.h"
#include "roiAnchor.h"

namespace GraphicsShapes {
class GraphicsItemRect;
}

namespace GraphicsRoi
{


class RectRoiAnchorPrivate;
class GRAPHICSROILIBSHARED_EXPORT RectRoiAnchor : public RoiAnchor
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
    // 构造函数
protected:
    RectRoiAnchor(RectRoiAnchorPrivate &dd, QGraphicsObject *scaleObj, GraphicsItemRect *parent);
public:
    RectRoiAnchor(QGraphicsObject *scaleObj, GraphicsItemRect *parent);
    RectRoiAnchor(QGraphicsObject *scaleObj, GraphicsItemRect *parent, AnchorPosType pos, AnchorMoveMode moveMode = EdgeMove, ShapeStyle shapeStyle = Rectangle, const QSizeF& size = QSizeF(9,9));

public:
    enum { Type = RectAnchor };
    virtual int type() const Q_DECL_OVERRIDE;
signals:
    void anchorPosTypeChanged(AnchorPosType pos);
    void anchorMoveModeChanged(AnchorMoveMode moveMode);
public:
    void setAnchor(QGraphicsObject *scaleObj, AnchorPosType pos, AnchorMoveMode moveMode = EdgeMove, ShapeStyle shapeStyle = Rectangle, const QSizeF& size = QSizeF(9,9));
    void setAnchorPos(QGraphicsObject *scaleObj, AnchorPosType pos, bool update = true);
    void setAnchorMoveMode(AnchorMoveMode moveMode = EdgeMove, bool update = true);
public slots:
    void updateAnchorPos(bool update = true);
protected:
    void init(GraphicsItemRect *parent);
protected:
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
private:
    Q_DISABLE_COPY(RectRoiAnchor)
    Q_DECLARE_PRIVATE_D(QGraphicsItem::d_ptr.data(), RectRoiAnchor)
};

}

#endif // RECTROIANCHOR_H
