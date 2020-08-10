#include "graphicsItemPoint.h"
#include "graphicsitempoint_p.h"

#include <QDebug>
#include <QVector2D>

namespace GraphicsShapes
{

void GraphicsItemPointPrivate::updateShapePath() const
{
    Q_Q(const GraphicsItemPoint);
    // 相对于场景，始终保持固定的像素大小。
    QPointF start(0,0);
    QPointF end(m_size.width(), m_size.height());
    qreal len = QLineF(q->mapFromScene(end), q->mapFromScene(start)).length();

    m_rect.setSize(QSizeF(len, len));
    m_rect.moveCenter(m_point);

    // 计算Shape
    QPainterPath path = calcPainterPath(m_rect);
    m_shapePath = GraphicsShapeItem::qt_graphicsItem_shapeFromPath(q, path, m_pen);
    // 计算boundingRect
    m_boundingRect = m_rect;
    qreal pw = m_pen.style() == Qt::NoPen ? qreal(0) : m_pen.widthF();
    if (pw > 0.0)
        m_boundingRect = m_shapePath.controlPointRect();
}

QPainterPath GraphicsItemPointPrivate::calcPainterPath(const QRectF &r) const
{
    QPainterPath path;
    switch (m_shapeStyle)
    {
    case GraphicsItemPoint::Rectangle:
    case GraphicsItemPoint::Cross:
        path.addRect(r);
        break;
    case GraphicsItemPoint::Circle:
        path.addEllipse(r);
        break;
    default:
        break;
    }
    return path;
}

GraphicsItemPoint::GraphicsItemPoint(GraphicsItemPointPrivate &dd, QGraphicsObject *scaleObj, QGraphicsObject *parent)
    : GraphicsItemRect(dd, parent)
{
    init(scaleObj);
}

GraphicsItemPoint::GraphicsItemPoint(QGraphicsObject *scaleObj, QGraphicsObject *parent)
    : GraphicsItemRect(*new GraphicsItemPointPrivate, parent)
{
    init(scaleObj);
}

GraphicsItemPoint::GraphicsItemPoint(const QPointF &point, const QSizeF &size, ShapeStyle style, QGraphicsObject *scaleObj, QGraphicsObject *parent)
    : GraphicsItemRect(*new GraphicsItemPointPrivate, parent)
{
    init(scaleObj);
    setPoint(point, size, style);
}

GraphicsItemPoint::~GraphicsItemPoint()
{

}

void GraphicsItemPoint::init(QGraphicsObject *scaleObj)
{
    //this->setCosmetic(true); // 线宽始终为1像素
    // this->setPenColor(QColor(Qt::red));
    // 相对于场景，始终保持固定的像素大小。 缩放后需要重新计算
    connect(scaleObj, &QGraphicsObject::scaleChanged, this, &GraphicsItemPoint::updateShape);
}

void GraphicsItemPoint::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_D(GraphicsItemPoint);
    Q_UNUSED(widget);
    painter->setPen(d->m_pen);
    painter->setBrush(d->m_brush);
    painter->setRenderHint(QPainter::Antialiasing, true);

    switch (d->m_shapeStyle)
    {
    case Rectangle:
        painter->drawRect(d->m_rect);
        break;
    case Circle:
        painter->drawEllipse(d->m_rect);
        break;
    case Cross:
    {
//        painter->drawEllipse(d->m_rect);
//        painter->drawPoint(d->m_rect.center());
        QPointF center = d->m_rect.center();
        painter->drawLine(QPointF(d->m_rect.left(), center.y()), QPointF(d->m_rect.right(), center.y()));
        painter->drawLine(QPointF(center.x(), d->m_rect.top()), QPointF(center.x(), d->m_rect.bottom()));
    }
        break;
    default:
        break;
    }

    if (option->state & QStyle::State_Selected)
        qt_graphicsItem_highlightSelected(this, painter, option);
}

void GraphicsItemPoint::setPoint(const QPointF &point, const QSizeF &size, ShapeStyle style, bool update)
{
    Q_D(GraphicsItemPoint);

    setPos(point, false);
    setSize(size, false);
    setShapeStyle(style, false);

    if (update)
        updateShape();
}

void GraphicsItemPoint::setShapeStyle(ShapeStyle style, bool update)
{
    Q_D(GraphicsItemPoint);
    if (style == d->m_shapeStyle)
        return;

    d->m_shapeStyle = style;

    if (update)
        updateShape();

    emit shapeStyleChanged(d->m_shapeStyle);
}

void GraphicsItemPoint::setPos(const QPointF &pos, bool update)
{
    Q_D(GraphicsItemPoint);
    if (pos == d->m_point)
        return;

    d->m_point = pos;

    if (update)
        updateShape();

    emit posChanged(d->m_point);
}

void GraphicsItemPoint::setSize(const QSizeF &size, bool update)
{
    Q_D(GraphicsItemPoint);
    if (size == d->m_size)
        return;

    d->m_size = size;

    if (update)
        updateShape();

    emit sizeChanged(d->m_size);
}

GraphicsItemPoint::ShapeStyle GraphicsItemPoint::shapeStyle()
{
    Q_D(GraphicsItemPoint);
    return d->m_shapeStyle;
}

QPointF GraphicsItemPoint::position()
{
    Q_D(GraphicsItemPoint);
    return d->m_point;
}

QSizeF GraphicsItemPoint::size()
{
    Q_D(GraphicsItemPoint);
    return d->m_size;
}

int GraphicsItemPoint::type() const
{
    return Type;
}

}
