#include "graphicsShapeItem.h"
#include "graphicsShapeItem_p.h"
#include <QBrush>
#include <QPen>
#include <QDebug>
#include <QGraphicsSceneContextMenuEvent>
#include <QMenu>
#include <QAction>
#include <QGraphicsScene>

namespace GraphicsShapes
{

/*!
    \internal

    Returns a QPainterPath of \a path when stroked with the \a pen.
    Ignoring dash pattern.
*/
QPainterPath GraphicsShapeItem::qt_graphicsItem_shapeFromPath(const QGraphicsItem *item, const QPainterPath &path, const QPen &pen)
{
    //qDebug() <<<< "start qt_graphicsItem_shapeFromPath";
    // We unfortunately need this hack as QPainterPathStroker will set a width of 1.0
    // if we pass a value of 0.0 to QPainterPathStroker::setWidth()

    if (path == QPainterPath() || pen == Qt::NoPen)
        return path;


    QPainterPathStroker ps;
    ps.setCapStyle(pen.capStyle());
    if (pen.isCosmetic())
    {
        qreal penW = QLineF(item->mapFromScene(QPointF(0,0)), item->mapFromScene(QPointF(0,1))).length();

        ps.setWidth(penW);
    }
    else
    {
        const qreal penWidthZero = qreal(0.00000001);
        if (pen.widthF() <= 0.0)
            ps.setWidth(penWidthZero);
        else
            ps.setWidth(pen.widthF());
    }

    ps.setJoinStyle(pen.joinStyle());
    ps.setMiterLimit(pen.miterLimit());

    QPainterPath p = ps.createStroke(path);
    p.addPath(path);
    return p;
}

/*!
    \internal

    Highlights \a item as selected.

    NOTE: This function is a duplicate of qt_graphicsItem_highlightSelected() in
          qgraphicssvgitem.cpp!
*/
void GraphicsShapeItem::qt_graphicsItem_highlightSelected(
    QGraphicsItem *item, QPainter *painter, const QStyleOptionGraphicsItem *option)
{
    //qDebug() <<<< "start qt_graphicsItem_highlightSelected";
    const QRectF murect = painter->transform().mapRect(QRectF(0, 0, 1, 1));
    if (qFuzzyIsNull(qMax(murect.width(), murect.height())))
        return;

    const QRectF mbrect = painter->transform().mapRect(item->boundingRect());
    if (qMin(mbrect.width(), mbrect.height()) < qreal(1.0))
        return;

    qreal itemPenWidth;
    switch (item->type()) {
        case QGraphicsEllipseItem::Type:
            itemPenWidth = static_cast<QGraphicsEllipseItem *>(item)->pen().widthF();
            break;
        case QGraphicsPathItem::Type:
            itemPenWidth = static_cast<QGraphicsPathItem *>(item)->pen().widthF();
            break;
        case QGraphicsPolygonItem::Type:
            itemPenWidth = static_cast<QGraphicsPolygonItem *>(item)->pen().widthF();
            break;
        case QGraphicsRectItem::Type:
            itemPenWidth = static_cast<QGraphicsRectItem *>(item)->pen().widthF();
            break;
        case QGraphicsSimpleTextItem::Type:
            itemPenWidth = static_cast<QGraphicsSimpleTextItem *>(item)->pen().widthF();
            break;
        case QGraphicsLineItem::Type:
            itemPenWidth = static_cast<QGraphicsLineItem *>(item)->pen().widthF();
            break;
        default:
            itemPenWidth = 1.0;
    }
    const qreal pad = itemPenWidth / 2;

    const qreal penWidth = 0; // cosmetic pen

    const QColor fgcolor = option->palette.windowText().color();
    const QColor bgcolor( // ensure good contrast against fgcolor
        fgcolor.red()   > 127 ? 0 : 255,
        fgcolor.green() > 127 ? 0 : 255,
        fgcolor.blue()  > 127 ? 0 : 255);

    painter->setPen(QPen(bgcolor, penWidth, Qt::SolidLine));
    painter->setBrush(Qt::NoBrush);
    painter->drawRect(item->boundingRect().adjusted(pad, pad, -pad, -pad));

    painter->setPen(QPen(option->palette.windowText(), 0, Qt::DashLine));
    painter->setBrush(Qt::NoBrush);
    painter->drawRect(item->boundingRect().adjusted(pad, pad, -pad, -pad));
}

void GraphicsShapeItem::updateShape()
{
    Q_D(const GraphicsShapeItem);

    prepareGeometryChange();
    d->updateShapePath();
    update();

    emit shapeChanged();
}

QRectF GraphicsShapeItem::boundingRect() const
{
    Q_D(const GraphicsShapeItem);
    return d->m_boundingRect;
}

QPainterPath GraphicsShapeItem::shape() const
{
    Q_D(const GraphicsShapeItem);
    return d->m_shapePath;
}


/*!
    \internal
*/
GraphicsShapeItem::GraphicsShapeItem(GraphicsShapeItemPrivate &dd, QGraphicsObject *parent)
    : QGraphicsObject(dd, parent)
{
}



/*!
    Returns the item's pen. If no pen has been set, this function returns
    QPen(), a default black solid line pen with 1 width.
*/
QPen GraphicsShapeItem::pen() const
{
    Q_D(const GraphicsShapeItem);
    return d->m_pen;
}

/*!
    Sets the pen for this item to \a pen.

    The pen is used to draw the item's outline.

    \sa pen()
*/
void GraphicsShapeItem::setPen(const QPen &pen, bool update)
{
    Q_D(GraphicsShapeItem);
    if (d->m_pen == pen)
        return;
    d->m_pen = pen;

    if (update)
        updateShape();
}


/*!
    Returns the item's brush, or an empty brush if no brush has been set.

    \sa setBrush()
*/
QBrush GraphicsShapeItem::brush() const
{
    Q_D(const GraphicsShapeItem);
    return d->m_brush;
}

/*!
    Sets the item's brush to \a brush.

    The item's brush is used to fill the item.

    If you use a brush with a QGradient, the gradient
    is relative to the item's coordinate system.

    \sa brush()
*/
void GraphicsShapeItem::setBrush(const QBrush &brush)
{
    Q_D(GraphicsShapeItem);
    if (d->m_brush == brush)
        return;
    d->m_brush = brush;

    update();
}
/*!
 * \brief GraphicsShapeItem::setBordeColor
 * \param c
 */
void GraphicsShapeItem::setPenColor(const QColor &c)
{
    Q_D(GraphicsShapeItem);
    d->m_pen.setColor(c);

    update();
}

/*!
 * \brief GraphicsShapeItem::setFillColor
 * \param c
 */
void GraphicsShapeItem::setBrushColor(const QColor &color)
{
    Q_D(GraphicsShapeItem);

    d->m_brush.setColor(color);
    if (color.alpha() != 0 && d->m_brush.style() == Qt::NoBrush)
        d->m_brush.setStyle(Qt::SolidPattern);

    update();
}

void GraphicsShapeItem::setCosmetic(bool b)
{
    Q_D(GraphicsShapeItem);
    d->m_pen.setCosmetic(b);

    updateShape();
}


/*!
    \reimp
*/
bool GraphicsShapeItem::isObscuredBy(const QGraphicsItem *item) const
{
    return QGraphicsItem::isObscuredBy(item);
}

/*!
    \reimp
*/
QPainterPath GraphicsShapeItem::opaqueArea() const
{
    Q_D(const GraphicsShapeItem);
    if (d->m_brush.isOpaque())
        return isClipped() ? clipPath() : shape();
    return QGraphicsItem::opaqueArea();
}

}
