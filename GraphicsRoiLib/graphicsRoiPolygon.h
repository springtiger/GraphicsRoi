#ifndef GRAPHICSPOLYGONROI_H
#define GRAPHICSPOLYGONROI_H

#include "graphicsroilib_global.h"
#include "graphicsItemPolygon.h"

#include <QPolygonF>

#include "graphicsAnchor.h"
#include "graphicsPolyLine.h"
#include "interfaceRoi.h"

class GRAPHICSROILIBSHARED_EXPORT GraphicsRoiPolygon : public GraphicsItemPolygon, public IRoi
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem IRoi)
public:
    explicit GraphicsRoiPolygon(QGraphicsObject *parent = Q_NULLPTR);
    explicit GraphicsRoiPolygon(const QPolygonF &polygon, QGraphicsObject *parent = Q_NULLPTR);

    void setPolygon(const QPolygonF &polygon);
    void append(const QPointF& point) ;
    void insert(int i, const QPointF &p) ;
    void updatePos(int i, const QPointF &p);
    void remove(int i);

    void setFirstAnchorBordeColor(const QColor& color);
    void setFirstAnchorFillColor(const QColor& color);
    virtual void setAnchorBordeColor(const QColor& color) override;
    virtual void setAnchorFillColor (const QColor& color) override;
    virtual void setRotatable(bool set) override;
    virtual void setResizable(bool set) override;

    enum { Type = UserType + UserType + 4 };
    int type() const Q_DECL_OVERRIDE;
signals:
    void inserted(int indexAt);
    void appended();
    void removed(int indexAt);
    void updated(int index);
    void polygonClosed();
protected slots:
    void anchorPressed();
    void anchorDoubleClicked();
protected:
    void init();
protected:
    virtual bool sceneEventFilter(QGraphicsItem *watched, QEvent *event) override;
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;
    virtual void hoverMoveEvent(QGraphicsSceneHoverEvent *event) override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

protected:
    QVector<GraphicsPolyLine*> m_lineItems;
    QVector<GraphicsAnchor*> m_anchors;

    QColor m_firstAnchorBordeColor  ;
    QColor m_firstAnchorFillColor   ;
};

#endif // GRAPHICSPOLYGONROI_H
