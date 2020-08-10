#include "graphicsItemPixmap.h"
#include "graphicsItemPixmap_p.h"
#include <QBitmap>
#include "graphicsShapeItem.h"
#include <QDebug>

namespace GraphicsShapes
{

/*!
    Constructs a GraphicsPixmapItem, using \a pixmap as the default pixmap.
    \a parent is passed to QGraphicsItem's constructor.

    \sa QGraphicsScene::addItem()
*/
GraphicsItemPixmap::GraphicsItemPixmap(const QPixmap &pixmap, QGraphicsObject *parent)
    : QGraphicsObject(*new GraphicsItemPixmapPrivate, parent)
{
    setPixmap(pixmap);
}

/*!
    Constructs a GraphicsPixmapItem. \a parent is passed to QGraphicsItem's
    constructor.

    \sa QGraphicsScene::addItem()
*/
GraphicsItemPixmap::GraphicsItemPixmap(QGraphicsObject *parent)
    : QGraphicsObject(*new GraphicsItemPixmapPrivate, parent)
{
}

/*!
    Destroys the GraphicsPixmapItem.
*/
GraphicsItemPixmap::~GraphicsItemPixmap()
{
}

/*!
    Sets the item's pixmap to \a pixmap.

    \sa pixmap()
*/
void GraphicsItemPixmap::setPixmap(const QPixmap &pixmap)
{
    Q_D(GraphicsItemPixmap);

    prepareGeometryChange();
    d->pixmap = pixmap;
    d->hasShape = false;
    update();

    emit pixmapChanged(d->pixmap);
}

/*!
    Returns the item's pixmap, or an invalid QPixmap if no pixmap has been
    set.

    \sa setPixmap()
*/
QPixmap GraphicsItemPixmap::pixmap() const
{
    Q_D(const GraphicsItemPixmap);
    return d->pixmap;
}

/*!
    Returns the transformation mode of the pixmap. The default mode is
    Qt::FastTransformation, which provides quick transformation with no
    smoothing.

    \sa setTransformationMode()
*/
Qt::TransformationMode GraphicsItemPixmap::transformationMode() const
{
    Q_D(const GraphicsItemPixmap);
    return d->transformationMode;
}

/*!
    Sets the pixmap item's transformation mode to \a mode, and toggles an
    update of the item. The default mode is Qt::FastTransformation, which
    provides quick transformation with no smoothing.

    Qt::SmoothTransformation enables QPainter::SmoothPixmapTransform on the
    painter, and the quality depends on the platform and viewport. The result
    is usually not as good as calling QPixmap::scale() directly.

    \sa transformationMode()
*/
void GraphicsItemPixmap::setTransformationMode(Qt::TransformationMode mode)
{
    Q_D(GraphicsItemPixmap);
    if (mode != d->transformationMode) {
        d->transformationMode = mode;
        update();
    }
}

/*!
    Returns the pixmap item's \e offset, which defines the point of the
    top-left corner of the pixmap, in local coordinates.

    \sa setOffset()
*/
QPointF GraphicsItemPixmap::offset() const
{
    Q_D(const GraphicsItemPixmap);
    return d->offset;
}

/*!
    Sets the pixmap item's offset to \a offset. GraphicsPixmapItem will draw
    its pixmap using \a offset for its top-left corner.

    \sa offset()
*/
void GraphicsItemPixmap::setOffset(const QPointF &offset)
{
    Q_D(GraphicsItemPixmap);
    if (d->offset == offset)
        return;
    prepareGeometryChange();
    d->offset = offset;
    d->hasShape = false;
    update();
}

/*!
    \fn void GraphicsPixmapItem::setOffset(qreal x, qreal y)
    \since 4.3

    This convenience function is equivalent to calling setOffset(QPointF(\a x, \a y)).
*/

/*!
    \reimp
*/
QRectF GraphicsItemPixmap::boundingRect() const
{
    Q_D(const GraphicsItemPixmap);
    if (d->pixmap.isNull())
        return QRectF();
    if (d->flags & ItemIsSelectable) {
        qreal pw = 1.0;
        return QRectF(d->offset, d->pixmap.size() / d->pixmap.devicePixelRatio()).adjusted(-pw/2, -pw/2, pw/2, pw/2);
    } else {
        return QRectF(d->offset, d->pixmap.size() / d->pixmap.devicePixelRatio());
    }
}

/*!
    \reimp
*/
QPainterPath GraphicsItemPixmap::shape() const
{
    Q_D(const GraphicsItemPixmap);
    if (!d->hasShape) {
        GraphicsItemPixmapPrivate *thatD = const_cast<GraphicsItemPixmapPrivate *>(d);
        thatD->updateShape();
        thatD->hasShape = true;
    }
    return d_func()->shape;
}

/*!
    \reimp
*/
bool GraphicsItemPixmap::contains(const QPointF &point) const
{
    return QGraphicsItem::contains(point);
}

/*!
    \reimp
*/
void GraphicsItemPixmap::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                                QWidget *widget)
{
    Q_D(GraphicsItemPixmap);
    Q_UNUSED(widget);

    painter->setRenderHint(QPainter::SmoothPixmapTransform,
                           (d->transformationMode == Qt::SmoothTransformation));

    painter->drawPixmap(d->offset, d->pixmap);

    if (option->state & QStyle::State_Selected)
        GraphicsShapeItem::qt_graphicsItem_highlightSelected(this, painter, option);
}

/*!
    \reimp
*/
bool GraphicsItemPixmap::isObscuredBy(const QGraphicsItem *item) const
{
    return QGraphicsItem::isObscuredBy(item);
}

/*!
    \reimp
*/
QPainterPath GraphicsItemPixmap::opaqueArea() const
{
    return shape();
}

/*!
    \reimp
*/
int GraphicsItemPixmap::type() const
{
    return Type;
}

/*!
    Returns the item's shape mode. The shape mode describes how
    GraphicsPixmapItem calculates its shape. The default mode is MaskShape.

    \sa setShapeMode(), ShapeMode
*/
GraphicsItemPixmap::ShapeMode GraphicsItemPixmap::shapeMode() const
{
    return d_func()->shapeMode;
}

/*!
    Sets the item's shape mode to \a mode. The shape mode describes how
    GraphicsPixmapItem calculates its shape. The default mode is MaskShape.

    \sa shapeMode(), ShapeMode
*/
void GraphicsItemPixmap::setShapeMode(ShapeMode mode)
{
    Q_D(GraphicsItemPixmap);
    if (d->shapeMode == mode)
        return;
    d->shapeMode = mode;
    d->hasShape = false;
}

GraphicsItemPixmap::GraphicsItemPixmap(GraphicsItemPixmapPrivate &dd, QGraphicsObject *parent)
    : QGraphicsObject(dd, parent)
{

}

/*!
    \internal
*/
bool GraphicsItemPixmap::supportsExtension(Extension extension) const
{
    Q_UNUSED(extension);
    return false;
}

/*!
    \internal
*/
void GraphicsItemPixmap::setExtension(Extension extension, const QVariant &variant)
{
    Q_UNUSED(extension);
    Q_UNUSED(variant);
}

/*!
    \internal
*/
QVariant GraphicsItemPixmap::extension(const QVariant &variant) const
{
    Q_UNUSED(variant);
    return QVariant();
}

void GraphicsItemPixmap::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    return QGraphicsObject::mouseMoveEvent(event);
}
}
