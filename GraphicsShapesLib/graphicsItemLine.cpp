#include "graphicsItemLine.h"
#include "graphicsItemLine_p.h"
#include "graphicsShapeItem.h"

namespace GraphicsShapes
{

void GraphicsItemLinePrivate::updateShapePath() const
{
    Q_Q(const GraphicsItemLine);
    // 计算Shape
    QPainterPath path;
    if (m_line == QLineF()) {
        m_shapePath = path;
        return;
    }

    path.moveTo(m_line.p1());
    path.lineTo(m_line.p2());

    m_shapePath = GraphicsShapeItem::qt_graphicsItem_shapeFromPath(q, path, m_pen);

    // 计算BoundingRect
    if (m_pen.widthF() == 0.0) {
        const qreal x1 = m_line.p1().x();
        const qreal x2 = m_line.p2().x();
        const qreal y1 = m_line.p1().y();
        const qreal y2 = m_line.p2().y();
        qreal lx = qMin(x1, x2);
        qreal rx = qMax(x1, x2);
        qreal ty = qMin(y1, y2);
        qreal by = qMax(y1, y2);
        m_boundingRect = QRectF(lx, ty, rx - lx, by - ty);
    }
    m_boundingRect = m_shapePath.controlPointRect();
}

GraphicsItemLine::GraphicsItemLine(GraphicsItemLinePrivate &dd, QGraphicsObject *parent)
    : GraphicsShapeItem(dd, parent)
{

}

/*!
    Constructs a GraphicsLineItem, using \a line as the default line. \a
    parent is passed to QGraphicsItem's constructor.

    \sa QGraphicsScene::addItem()
*/
GraphicsItemLine::GraphicsItemLine(const QLineF &line, QGraphicsObject *parent)
    : GraphicsShapeItem(*new GraphicsItemLinePrivate, parent)
{
    setLine(line);
}

/*!
    Constructs a GraphicsLineItem, using the line between (\a x1, \a y1) and
    (\a x2, \a y2) as the default line.  \a parent is passed to
    QGraphicsItem's constructor.

    \sa QGraphicsScene::addItem()
*/
GraphicsItemLine::GraphicsItemLine(qreal x1, qreal y1, qreal x2, qreal y2, QGraphicsObject *parent)
    : GraphicsShapeItem(*new GraphicsItemLinePrivate, parent)
{
    setLine(x1, y1, x2, y2);
}



/*!
    Constructs a GraphicsLineItem. \a parent is passed to QGraphicsItem's
    constructor.

    \sa QGraphicsScene::addItem()
*/
GraphicsItemLine::GraphicsItemLine(QGraphicsObject *parent)
    : GraphicsShapeItem(*new GraphicsItemLinePrivate, parent)
{
}

/*!
    Destroys the GraphicsLineItem.
*/
GraphicsItemLine::~GraphicsItemLine()
{
}


/*!
    Returns the item's line, or a null line if no line has been set.

    \sa setLine()
*/
QLineF GraphicsItemLine::line() const
{
    Q_D(const GraphicsItemLine);
    return d->m_line;
}

void GraphicsItemLine::setP1(const QPointF &p, bool update)
{
    Q_D(GraphicsItemLine);

    if (p == d->m_line.p1())
        return;

    d->m_line.setP1(p);

    if (update)
        updateShape();

    emit lineChanged(d->m_line);
}

void GraphicsItemLine::setP2(const QPointF &p, bool update)
{
    Q_D(GraphicsItemLine);

    if (p == d->m_line.p2())
        return;

    d->m_line.setP2(p);

    if (update)
        updateShape();

    emit lineChanged(d->m_line);
}

/*!
    Sets the item's line to be the given \a line.

    \sa line()
*/
void GraphicsItemLine::setLine(const QLineF &line, bool update)
{
    Q_D(GraphicsItemLine);
    if (d->m_line == line)
        return;

    d->m_line = line;

    if (update)
        updateShape();

    emit lineChanged(d->m_line);
}

/*!
    \fn void GraphicsLineItem::setLine(qreal x1, qreal y1, qreal x2, qreal y2)
    \overload

    Sets the item's line to be the line between (\a x1, \a y1) and (\a
    x2, \a y2).

    This is the same as calling \c {setLine(QLineF(x1, y1, x2, y2))}.
*/



/*!
    \reimp
*/
void GraphicsItemLine::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_D(GraphicsItemLine);
    Q_UNUSED(widget);
    painter->setPen(d->m_pen);
    painter->drawLine(d->m_line);

    if (option->state & QStyle::State_Selected)
        GraphicsShapeItem::qt_graphicsItem_highlightSelected(this, painter, option);
}


/*!
    \reimp
*/
int GraphicsItemLine::type() const
{
    return Type;
}

}

