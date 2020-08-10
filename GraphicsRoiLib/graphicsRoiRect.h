#ifndef GRAPHICSRECTROI_H
#define GRAPHICSRECTROI_H

#include "graphicsroilib_global.h"
#include "graphicsItemRect.h"
#include "graphicsAnchor.h"
#include "graphicsShapeItem.h"
#include "interfaceRoi.h"

class GRAPHICSROILIBSHARED_EXPORT GraphicsRoiRect : public GraphicsItemRect, public IRoi
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem IRoi)
public:
    explicit GraphicsRoiRect(const QRectF &rect, QGraphicsObject *parent = Q_NULLPTR);
    explicit GraphicsRoiRect(qreal x, qreal y, qreal w, qreal h, QGraphicsObject *parent = Q_NULLPTR);
    explicit GraphicsRoiRect(const QPointF &center, const QSizeF &size, QGraphicsObject *parent = Q_NULLPTR);
    ~GraphicsRoiRect();

    enum { Type = UserType + UserType + 1 };
    int type() const Q_DECL_OVERRIDE;
public:
    void setRect(const QRectF &rect);
    void setAnchorBordeColor(const QColor& color) override;
    void setAnchorFillColor(const QColor& color) override;
    void setRotatable(bool set) override;
    void setResizable(bool set) override;
signals:
    void rectChanged();
protected:
    void init();
private:
    GraphicsAnchor *m_anchorLeft  ;
    GraphicsAnchor *m_anchorRight ;
    GraphicsAnchor *m_anchorTop   ;
    GraphicsAnchor *m_anchorBottom;

    GraphicsAnchor *m_anchorTopLeft    ;
    GraphicsAnchor *m_anchorTopRight   ;
    GraphicsAnchor *m_anchorBottomLeft ;
    GraphicsAnchor *m_anchorBottomRight;

    GraphicsAnchor *m_anchorRotater    ;
protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    virtual void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;
    virtual void hoverMoveEvent(QGraphicsSceneHoverEvent *event) override;
private:
    friend class GraphicsAnchor;
};

#endif // GRAPHICSRECTROI_H
