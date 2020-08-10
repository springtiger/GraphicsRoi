#include "graphicsItemRect.h"
#include "graphicsItemRect_p.h"

#include <QDebug>

namespace GraphicsShapes
{

void GraphicsItemRectPrivate::updateShapePath() const
{
    Q_Q(const GraphicsItemRect);
    // 计算Shape
    QPainterPath path;
    path.addRect(m_rect);
    m_shapePath = GraphicsShapeItem::qt_graphicsItem_shapeFromPath(q, path, m_pen);
    // 计算boundingRect
    m_boundingRect = m_rect;
    qreal pw = m_pen.style() == Qt::NoPen ? qreal(0) : m_pen.widthF();
    if (pw > 0.0)
        m_boundingRect = m_shapePath.controlPointRect();
}

GraphicsItemRect::GraphicsItemRect(GraphicsItemRectPrivate &dd, QGraphicsObject *parent)
    : GraphicsShapeItem(dd, parent)
{

}

/*!
    Constructs a GraphicsRectItem, using \a rect as the default rectangle.
    \a parent is passed to GraphicsShapeItem's constructor.

    \sa QGraphicsScene::addItem()
*/
GraphicsItemRect::GraphicsItemRect(const QRectF &rect, QGraphicsObject *parent)
    : GraphicsShapeItem(*new GraphicsItemRectPrivate, parent)
{
    setRect(rect);
}

/*!
    \fn GraphicsRectItem::GraphicsRectItem(qreal x, qreal y, qreal width, qreal height,
                                     QGraphicsItem *parent)

    Constructs a GraphicsRectItem with a default rectangle defined
    by (\a x, \a y) and the given \a width and \a height.

    \a parent is passed to GraphicsShapeItem's constructor.

    \sa QGraphicsScene::addItem()
*/
GraphicsItemRect::GraphicsItemRect(qreal x, qreal y, qreal w, qreal h,
                                     QGraphicsObject *parent)
    : GraphicsShapeItem(*new GraphicsItemRectPrivate, parent)
{
    setRect(QRectF(x, y, w, h));
}

/*!
    Constructs a GraphicsRectItem. \a parent is passed to
    GraphicsShapeItem's constructor.

    \sa QGraphicsScene::addItem()
*/
GraphicsItemRect::GraphicsItemRect(QGraphicsObject *parent)
    : GraphicsShapeItem(*new GraphicsItemRectPrivate, parent)
{
}

/*!
    Destroys the GraphicsRectItem.
*/
GraphicsItemRect::~GraphicsItemRect()
{
}

/*!
    Returns the item's rectangle.

    \sa setRect()
*/
QRectF GraphicsItemRect::rect() const
{
    //qDebug() << "start rect";
    Q_D(const GraphicsItemRect);
    return d->m_rect;
}


/*!
    \fn void GraphicsRectItem::setRect(const QRectF &rectangle)

    Sets the item's rectangle to be the given \a rectangle.

    \sa rect()
*/
void GraphicsItemRect::setRect(const QRectF &rect, bool update)
{
    Q_D(GraphicsItemRect);
    if (d->m_rect == rect)
        return;

    d->m_rect = rect;

    setTransformOriginPoint(d->m_rect.center());

    if (update)
        updateShape();

    emit rectChanged(d->m_rect);
}



/*!
    \fn void GraphicsRectItem::setRect(qreal x, qreal y, qreal width, qreal height)
    \fn void QGraphicsEllipseItem::setRect(qreal x, qreal y, qreal width, qreal height)

    Sets the item's rectangle to the rectangle defined by (\a x, \a y)
    and the given \a width and \a height.

    This convenience function is equivalent to calling \c
    {setRect(QRectF(x, y, width, height))}

    \sa rect()
*/


/*!
    \reimp
*/
void GraphicsItemRect::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                              QWidget *widget)
{
    Q_D(GraphicsItemRect);
    Q_UNUSED(widget);
    painter->setPen(d->m_pen);
    painter->setBrush(d->m_brush);

    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->drawRect(d->m_rect.normalized());

    if (option->state & QStyle::State_Selected)
        qt_graphicsItem_highlightSelected(this, painter, option);
}



/*!
    \reimp
*/
int GraphicsItemRect::type() const
{
    return Type;
}


}
