#ifndef GRAPHICSPATHITEM_P_H
#define GRAPHICSPATHITEM_P_H

#include "graphicsShapeItem_p.h"
#include "graphicsItemPath.h"
#include "graphicsshapeslib_global.h"

namespace GraphicsShapes
{

/*!
    \class GraphicsPathItem
    \brief The GraphicsPathItem class provides a path item that you
    can add to a QGraphicsScene.
    \since 4.2
    \ingroup graphicsview-api
    \inmodule QtWidgets

    To set the item's path, pass a QPainterPath to GraphicsPathItem's
    constructor, or call the setPath() function. The path() function
    returns the current path.

    \image graphicsview-pathitem.png

    GraphicsPathItem uses the path to provide a reasonable
    implementation of boundingRect(), shape(), and contains(). The
    paint() function draws the path using the item's associated pen
    and brush, which you can set by calling the setPen() and
    setBrush() functions.

    \sa QGraphicsRectItem, QGraphicsEllipseItem, QGraphicsPolygonItem,
    QGraphicsTextItem, QGraphicsLineItem, QGraphicsPixmapItem, {Graphics
    View Framework}
*/

class GRAPHICSSHAPESLIBSHARED_EXPORT GraphicsItemPathPrivate : public GraphicsShapeItemPrivate
{
    Q_DECLARE_PUBLIC(GraphicsItemPath)
public:
    inline GraphicsItemPathPrivate()
        : GraphicsShapeItemPrivate()
    {

    }

public:
    virtual void updateShapePath()const override;

public:
    mutable QPainterPath m_path;
};

}
#endif // GRAPHICSPATHITEM_P_H
