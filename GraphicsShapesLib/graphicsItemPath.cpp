#include "graphicsItemPath.h"
#include "graphicsItemPath_p.h"

namespace GraphicsShapes
{

void GraphicsItemPathPrivate::updateShapePath() const
{
    Q_Q(const GraphicsItemPath);

    // 计算Shape
    m_shapePath = GraphicsShapeItem::qt_graphicsItem_shapeFromPath(q, m_path, m_pen);
    // 计算BoundingRect
    qreal pw = m_pen.style() == Qt::NoPen ? qreal(0) : m_pen.widthF();
    if (pw == 0.0)
        m_boundingRect = m_path.controlPointRect();
    else {
        m_boundingRect = m_shapePath.controlPointRect();
    }
}

/*!
    Constructs a QGraphicsPath item using \a path as the default path. \a
    parent is passed to GraphicsShapeItem's constructor.

    \sa QGraphicsScene::addItem()
*/
GraphicsItemPath::GraphicsItemPath(const QPainterPath &path,
                                     QGraphicsObject *parent)
    : GraphicsShapeItem(*new GraphicsItemPathPrivate, parent)
{
    if (!path.isEmpty())
        setPath(path);
}

/*!
    Constructs a QGraphicsPath. \a parent is passed to
    GraphicsShapeItem's constructor.

    \sa QGraphicsScene::addItem()
*/
GraphicsItemPath::GraphicsItemPath(QGraphicsObject *parent)
    : GraphicsShapeItem(*new GraphicsItemPathPrivate, parent)
{
}

/*!
    Destroys the GraphicsPathItem.
*/
GraphicsItemPath::~GraphicsItemPath()
{
}

/*!
    Returns the item's path as a QPainterPath. If no item has been set, an
    empty QPainterPath is returned.

    \sa setPath()
*/
QPainterPath GraphicsItemPath::path() const
{
    Q_D(const GraphicsItemPath);
    return d->m_path;
}

/*!
    Sets the item's path to be the given \a path.

    \sa path()
*/
void GraphicsItemPath::setPath(const QPainterPath &path, bool update)
{
    Q_D(GraphicsItemPath);
    if (d->m_path == path)
        return;

    d->m_path = path;

    if (update)
        updateShape();

    emit pathChanged(d->m_path);
}


/*!
    \reimp
*/
void GraphicsItemPath::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                              QWidget *widget)
{
    Q_D(GraphicsItemPath);
    Q_UNUSED(widget);
    painter->setPen(d->m_pen);
    painter->setBrush(d->m_brush);
    painter->drawPath(d->m_path);

    if (option->state & QStyle::State_Selected)
        qt_graphicsItem_highlightSelected(this, painter, option);
}



/*!
    \reimp
*/
int GraphicsItemPath::type() const
{
    return Type;
}

GraphicsItemPath::GraphicsItemPath(GraphicsItemPathPrivate &dd, QGraphicsObject *parent)
    : GraphicsShapeItem(dd, parent)
{

}


}
