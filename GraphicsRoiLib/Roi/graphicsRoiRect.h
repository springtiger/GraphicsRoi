#ifndef GRAPHICSRECTROI_H
#define GRAPHICSRECTROI_H

#include "graphicsroilib_global.h"

#include "graphicsItemRect.h"
#include "interfaceRoi.h"
#include "roiPart/rectRoiAnchor.h"

namespace GraphicsRoi
{

class GraphicsRoiRectPrivate;
class GRAPHICSROILIBSHARED_EXPORT GraphicsRoiRect : public GraphicsItemRect, public IRoi
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem IRoi)
protected:
    GraphicsRoiRect(GraphicsRoiRectPrivate &dd, QGraphicsObject *parent);
public:
    explicit GraphicsRoiRect(const QRectF &rect, QGraphicsObject *parent = Q_NULLPTR, AnchorMoveMode mode = EdgeMove);
    explicit GraphicsRoiRect(qreal x, qreal y, qreal w, qreal h, QGraphicsObject *parent = Q_NULLPTR, AnchorMoveMode mode = EdgeMove);
    explicit GraphicsRoiRect(const QPointF &center, const QSizeF &size, QGraphicsObject *parent = Q_NULLPTR, AnchorMoveMode mode = EdgeMove);
    ~GraphicsRoiRect();

    enum { Type = RectRoi };
    int type() const Q_DECL_OVERRIDE;
public:
    void setAnchorBordeColor(const QColor& color) override;
    void setAnchorFillColor(const QColor& color) override;
    void setResizeAnchorVisible(bool set);
    void setRotateAnchorVisible(bool set);
    void setRotatable(bool set) override;
    void setResizable(bool set) override;
    void setMovable(bool set) override;
    void setCentreVisible(bool set) ;
    void setAnchorAutoHide(bool set) ;

signals:
    void pressed();
protected:
    void init(QGraphicsObject *parent, AnchorMoveMode mode = EdgeMove);

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    virtual void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;
    virtual void hoverMoveEvent(QGraphicsSceneHoverEvent *event) override;
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
private:
    Q_DISABLE_COPY(GraphicsRoiRect)
    Q_DECLARE_PRIVATE_D(QGraphicsItem::d_ptr.data(), GraphicsRoiRect)
};

}

#endif // GRAPHICSRECTROI_H
