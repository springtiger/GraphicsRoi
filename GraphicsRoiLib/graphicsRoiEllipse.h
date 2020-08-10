#ifndef GRAPHICSELLIPSEROI_H
#define GRAPHICSELLIPSEROI_H

#include "graphicsroilib_global.h"
#include "graphicsItemEllipse.h"
#include "graphicsAnchor.h"
#include "interfaceRoi.h"

class GRAPHICSROILIBSHARED_EXPORT GraphicsRoiEllipse : public GraphicsItemEllipse, public IRoi
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem IRoi)
public:
    explicit GraphicsRoiEllipse(const QRectF &rect, QGraphicsObject *parent = Q_NULLPTR);
    explicit GraphicsRoiEllipse(qreal x, qreal y, qreal w, qreal h, QGraphicsObject *parent = Q_NULLPTR);
    explicit GraphicsRoiEllipse(const QPointF &center, const QSizeF &size, QGraphicsObject *parent = Q_NULLPTR);

    enum { Type = UserType + UserType + 2 };
    int type() const Q_DECL_OVERRIDE;

protected:
    void init();
    void setAnchorBordeColor(const QColor& color) override;
    void setAnchorFillColor (const QColor& color) override;
    void setRotatable(bool set) override;
    void setResizable(bool set) override;
protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR) Q_DECL_OVERRIDE;
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
    GraphicsAnchor *m_anchorAngleStart ;
    GraphicsAnchor *m_anchorAngleSpan  ;
private:
    friend class GraphicsAnchor;
};

#endif // GRAPHICSELLIPSEROI_H
