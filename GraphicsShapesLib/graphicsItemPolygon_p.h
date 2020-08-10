#ifndef GRAPHICSPOLYGONITEM_P_H
#define GRAPHICSPOLYGONITEM_P_H

#include "graphicsShapeItem_p.h"
#include "graphicsItemPolygon.h"
#include "graphicsshapeslib_global.h"

namespace GraphicsShapes
{

/*!
    \class GraphicsPolygonItem
    \brief The GraphicsPolygonItem class provides a polygon item that you
    can add to a QGraphicsScene.
    \since 4.2
    \ingroup graphicsview-api
    \inmodule QtWidgets

    To set the item's polygon, pass a QPolygonF to
    GraphicsPolygonItem's constructor, or call the setPolygon()
    function. The polygon() function returns the current polygon.

    \image graphicsview-polygonitem.png

    GraphicsPolygonItem uses the polygon and the pen width to provide
    a reasonable implementation of boundingRect(), shape(), and
    contains(). The paint() function draws the polygon using the
    item's associated pen and brush, which you can set by calling the
    setPen() and setBrush() functions.

    \sa QGraphicsPathItem, QGraphicsRectItem, QGraphicsEllipseItem,
    QGraphicsTextItem, QGraphicsLineItem, QGraphicsPixmapItem, {Graphics
    View Framework}
*/

class GRAPHICSSHAPESLIBSHARED_EXPORT GraphicsItemPolygonPrivate : public GraphicsShapeItemPrivate
{
    Q_DECLARE_PUBLIC(GraphicsItemPolygon)
public:
    inline GraphicsItemPolygonPrivate()
        : GraphicsShapeItemPrivate()
        , m_fillRule(Qt::OddEvenFill)
    { }

public:
    virtual void updateShapePath()const override;
public:
    mutable QPolygonF m_polygon;
    Qt::FillRule m_fillRule;
};

}

#endif // GRAPHICSPOLYGONITEM_P_H
