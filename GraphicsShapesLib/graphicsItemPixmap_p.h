#ifndef GRAPHICSPIXMAPITEM_P_H
#define GRAPHICSPIXMAPITEM_P_H

#include "graphicsshapeslib_global.h"
#include "graphicsItemPixmap.h"
#include <QBitmap>
#include <QtWidgets\private\qgraphicsitem_p.h>


/*!
    \class GraphicsPixmapItem
    \brief The GraphicsPixmapItem class provides a pixmap item that you can add to
    a QGraphicsScene.
    \since 4.2
    \ingroup graphicsview-api
    \inmodule QtWidgets

    To set the item's pixmap, pass a QPixmap to GraphicsPixmapItem's
    constructor, or call the setPixmap() function. The pixmap()
    function returns the current pixmap.

    GraphicsPixmapItem uses pixmap's optional alpha mask to provide a
    reasonable implementation of boundingRect(), shape(), and contains().

    \image graphicsview-pixmapitem.png

    The pixmap is drawn at the item's (0, 0) coordinate, as returned by
    offset(). You can change the drawing offset by calling setOffset().

    You can set the pixmap's transformation mode by calling
    setTransformationMode(). By default, Qt::FastTransformation is used, which
    provides fast, non-smooth scaling. Qt::SmoothTransformation enables
    QPainter::SmoothPixmapTransform on the painter, and the quality depends on
    the platform and viewport. The result is usually not as good as calling
    QPixmap::scale() directly. Call transformationMode() to get the current
    transformation mode for the item.

    \sa QGraphicsPathItem, QGraphicsRectItem, QGraphicsEllipseItem,
    QGraphicsTextItem, QGraphicsPolygonItem, QGraphicsLineItem,
    {Graphics View Framework}
*/

/*!
    \enum GraphicsPixmapItem::ShapeMode

    This enum describes how GraphicsPixmapItem calculates its shape and
    opaque area.

    The default value is MaskShape.

    \value MaskShape The shape is determined by calling QPixmap::mask().
    This shape includes only the opaque pixels of the pixmap.
    Because the shape is more complex, however, it can be slower than the other modes,
    and uses more memory.

    \value BoundingRectShape The shape is determined by tracing the outline of
    the pixmap. This is the fastest shape mode, but it does not take into account
    any transparent areas on the pixmap.

    \value HeuristicMaskShape The shape is determine by calling
    QPixmap::createHeuristicMask().  The performance and memory consumption
    is similar to MaskShape.
*/
extern QPainterPath qt_regionToPath(const QRegion &region);

namespace GraphicsShapes
{

class GRAPHICSSHAPESLIBSHARED_EXPORT GraphicsItemPixmapPrivate : public QGraphicsItemPrivate
{
    Q_DECLARE_PUBLIC(GraphicsItemPixmap)
public:
    GraphicsItemPixmapPrivate()
        : transformationMode(Qt::FastTransformation),
        shapeMode(GraphicsItemPixmap::MaskShape),
        hasShape(false)
    {}

    mutable QPixmap pixmap;
    Qt::TransformationMode transformationMode;
    QPointF offset;
    GraphicsItemPixmap::ShapeMode shapeMode;
    QPainterPath shape;
    bool hasShape;

    void updateShape()
    {
        shape = QPainterPath();
        switch (shapeMode) {
        case GraphicsItemPixmap::MaskShape: {
            QBitmap mask = pixmap.mask();
            if (!mask.isNull()) {
                shape = qt_regionToPath(QRegion(mask).translated(offset.toPoint()));
                break;
            }
            Q_FALLTHROUGH();
        }
        case GraphicsItemPixmap::BoundingRectShape:
            shape.addRect(QRectF(offset.x(), offset.y(), pixmap.width(), pixmap.height()));
            break;
        case GraphicsItemPixmap::HeuristicMaskShape:
#ifndef QT_NO_IMAGE_HEURISTIC_MASK
            shape = qt_regionToPath(QRegion(pixmap.createHeuristicMask()).translated(offset.toPoint()));
#else
            shape.addRect(QRectF(offset.x(), offset.y(), pixmap.width(), pixmap.height()));
#endif
            break;
        }
    }
};

}

#endif // GRAPHICSPIXMAPITEM_P_H
