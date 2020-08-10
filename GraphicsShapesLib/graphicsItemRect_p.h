#ifndef GRAPHICSRECTITEM_P_H
#define GRAPHICSRECTITEM_P_H

#include "graphicsshapeslib_global.h"
#include "graphicsShapeItem_p.h"
#include "graphicsItemRect.h"

namespace GraphicsShapes
{

/*!
    \class GraphicsRectItem
    \brief The GraphicsRectItem class provides a rectangle item that you
    can add to a QGraphicsScene.
    \since 4.2
    \ingroup graphicsview-api
    \inmodule QtWidgets

    To set the item's rectangle, pass a QRectF to GraphicsRectItem's
    constructor, or call the setRect() function. The rect() function
    returns the current rectangle.

    \image graphicsview-rectitem.png

    GraphicsRectItem uses the rectangle and the pen width to provide
    a reasonable implementation of boundingRect(), shape(), and
    contains(). The paint() function draws the rectangle using the
    item's associated pen and brush, which you can set by calling the
    setPen() and setBrush() functions.

    \note The rendering of invalid rectangles, such as those with negative
    widths or heights, is undefined. If you cannot be sure that you are
    using valid rectangles (for example, if you are creating
    rectangles using data from an unreliable source) then you should
    use QRectF::normalized() to create normalized rectangles, and use
    those instead.

    \sa QGraphicsPathItem, QGraphicsEllipseItem, QGraphicsPolygonItem,
    QGraphicsTextItem, QGraphicsLineItem, QGraphicsPixmapItem, {Graphics
    View Framework}
*/

class GRAPHICSSHAPESLIBSHARED_EXPORT GraphicsItemRectPrivate : public GraphicsShapeItemPrivate
{
    Q_DECLARE_PUBLIC(GraphicsItemRect)
public:
    inline GraphicsItemRectPrivate()
        : GraphicsShapeItemPrivate()
    {

    }

protected:
    virtual void updateShapePath()const override;
public:
    mutable QRectF m_rect;
};

}

#endif // GRAPHICSRECTITEM_P_H
