#ifndef GRAPHICSCIRCLEROI_H
#define GRAPHICSCIRCLEROI_H

#include "graphicsroilib_global.h"
#include "graphicsItemEllipse.h"
#include "graphicsAnchor.h"
#include "interfaceRoi.h"

class GRAPHICSROILIBSHARED_EXPORT GraphicsRoiCircle : public GraphicsItemEllipse, public IRoi
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem IRoi)
public:
    explicit GraphicsRoiCircle(const QPointF &center, qreal radius, QGraphicsObject *parent = Q_NULLPTR);

    enum { Type = UserType + UserType + 3 };
    int type() const Q_DECL_OVERRIDE;

public:
    void setCenter(const QPointF &center);
    void setRadius(qreal radius);
    void setCenterAndRadius(const QPointF &center, qreal radius);
    void setAnchorBordeColor(const QColor& color) override;
    void setAnchorFillColor (const QColor& color) override;
    void setRotatable(bool set) override;
    void setResizable(bool set) override;
private:
    void setRect(const QRectF &rect);
signals:
    void rectChanged();
    void radiusChanged();
protected:
    void init();
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
private:
    friend class GraphicsAnchor;
};

#endif // GRAPHICSCIRCLEROI_H
