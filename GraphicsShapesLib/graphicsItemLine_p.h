#ifndef GRAPHICSLINEITEM_P_H
#define GRAPHICSLINEITEM_P_H

#include "graphicsshapeslib_global.h"

#include "graphicsItemLine.h"
#include "graphicsShapeItem_p.h"

namespace GraphicsShapes
{

/*!
    \class GraphicsLineItem
    \brief The GraphicsLineItem class provides a line item that you can add to a
    QGraphicsScene.
    \since 4.2
    \ingroup graphicsview-api
    \inmodule QtWidgets

    To set the item's line, pass a QLineF to GraphicsLineItem's
    constructor, or call the setLine() function. The line() function
    returns the current line. By default the line is black with a
    width of 0, but you can change this by calling setPen().

    \image graphicsview-lineitem.png

    GraphicsLineItem uses the line and the pen width to provide a reasonable
    implementation of boundingRect(), shape(), and contains(). The paint()
    function draws the line using the item's associated pen.

    \sa QGraphicsPathItem, QGraphicsRectItem, QGraphicsEllipseItem,
    QGraphicsTextItem, QGraphicsPolygonItem, QGraphicsPixmapItem,
    {Graphics View Framework}
*/

class GRAPHICSSHAPESLIBSHARED_EXPORT GraphicsItemLinePrivate : public GraphicsShapeItemPrivate
{
    Q_DECLARE_PUBLIC(GraphicsItemLine)
public:
    inline GraphicsItemLinePrivate()
        : GraphicsShapeItemPrivate()
    {

    }

public:
    virtual void updateShapePath()const override;

public:
    mutable QLineF m_line;
};
}
#endif // GRAPHICSLINEITEM_P_H
