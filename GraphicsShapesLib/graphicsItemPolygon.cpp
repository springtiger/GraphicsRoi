#include "graphicsItemPolygon.h"
#include "graphicsItemPolygon_p.h"

namespace GraphicsShapes
{

void GraphicsItemPolygonPrivate::updateShapePath() const
{
    Q_Q(const GraphicsItemPolygon);

    // 计算Shape
    QPainterPath path;
    path.addPolygon(m_polygon);
    m_shapePath = GraphicsShapeItem::qt_graphicsItem_shapeFromPath(q, path, m_pen);
    // 计算BoundingRect
    qreal pw = m_pen.style() == Qt::NoPen ? qreal(0) : m_pen.widthF();
    if (pw == 0.0)
        m_boundingRect = m_polygon.boundingRect();
    else
        m_boundingRect = m_shapePath.controlPointRect();
}


/*!
    Constructs a GraphicsPolygonItem with \a polygon as the default
    polygon. \a parent is passed to GraphicsShapeItem's constructor.

    \sa QGraphicsScene::addItem()
*/
GraphicsItemPolygon::GraphicsItemPolygon(const QPolygonF &polygon, QGraphicsObject *parent)
    : GraphicsShapeItem(*new GraphicsItemPolygonPrivate, parent)
{
    setPolygon(polygon);
}

/*!
    Constructs a GraphicsPolygonItem. \a parent is passed to
    GraphicsShapeItem's constructor.

    \sa QGraphicsScene::addItem()
*/
GraphicsItemPolygon::GraphicsItemPolygon(QGraphicsObject *parent)
    : GraphicsShapeItem(*new GraphicsItemPolygonPrivate, parent)
{
}

/*!
    Destroys the GraphicsPolygonItem.
*/
GraphicsItemPolygon::~GraphicsItemPolygon()
{
}

/*!
    Returns the item's polygon, or an empty polygon if no polygon
    has been set.

    \sa setPolygon()
*/
QPolygonF GraphicsItemPolygon::polygon() const
{
    Q_D(const GraphicsItemPolygon);
    return d->m_polygon;
}

/*!
    Sets the item's polygon to be the given \a polygon.

    \sa polygon()
*/
void GraphicsItemPolygon::setPolygon(const QPolygonF &polygon)
{
    Q_D(GraphicsItemPolygon);
    if (d->m_polygon == polygon)
        return;

    d->m_polygon = polygon;

    updateShape();

    emit polygonChanged(d->m_polygon);
}

void GraphicsItemPolygon::append(const QPointF &p)
{
    Q_D(GraphicsItemPolygon);

    d->m_polygon.append(p);

    updateShape();

    emit polygonChanged(d->m_polygon);
}

void GraphicsItemPolygon::insert(int i, const QPointF &p)
{
    Q_D(GraphicsItemPolygon);
    if(i < 0 || i > polygon().size())
        return;

    d->m_polygon.insert(i, p);

    updateShape();

    emit polygonChanged(d->m_polygon);
}

void GraphicsItemPolygon::updatePos(int i, const QPointF &p)
{
    Q_D(GraphicsItemPolygon);

    if(i < 0 || i >= polygon().size())
        return;

    d->m_polygon[i] = p;

    updateShape();

    emit polygonChanged(d->m_polygon);
}

void GraphicsItemPolygon::remove(int i)
{
    Q_D(GraphicsItemPolygon);

    if(i < 0 || i >= polygon().size())
        return;

    d->m_polygon.remove(i);

    updateShape();

    emit polygonChanged(d->m_polygon);
}

/*!
     Returns the fill rule of the polygon. The default fill rule is
     Qt::OddEvenFill.

     \sa setFillRule(), QPainterPath::fillRule(), QPainter::drawPolygon()
*/
Qt::FillRule GraphicsItemPolygon::fillRule() const
{
     Q_D(const GraphicsItemPolygon);
     return d->m_fillRule;
}

/*!
     Sets the fill rule of the polygon to \a rule. The default fill rule is
     Qt::OddEvenFill.

     \sa fillRule(), QPainterPath::fillRule(), QPainter::drawPolygon()
*/
void GraphicsItemPolygon::setFillRule(Qt::FillRule rule)
{
     Q_D(GraphicsItemPolygon);
     if (rule != d->m_fillRule) {
         d->m_fillRule = rule;
         update();
     }
}


/*!
    \reimp
*/
void GraphicsItemPolygon::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_D(GraphicsItemPolygon);
    Q_UNUSED(widget);
    painter->setPen(d->m_pen);
    painter->setBrush(d->m_brush);
    painter->drawPolygon(d->m_polygon, d->m_fillRule);

    if (option->state & QStyle::State_Selected)
        qt_graphicsItem_highlightSelected(this, painter, option);
}


/*!
    \reimp
*/
int GraphicsItemPolygon::type() const
{
    return Type;
}

GraphicsItemPolygon::GraphicsItemPolygon(GraphicsItemPolygonPrivate &dd, QGraphicsObject *parent)
    : GraphicsShapeItem(dd, parent)
{

}
}

