#include "graphicsItemEllipse.h"
#include "graphicsItemEllipse_p.h"

namespace GraphicsShapes
{


void GraphicsItemEllipsePrivate::updateShapePath() const
{
    Q_Q(const GraphicsItemEllipse);
    // 计算Shape
    QPainterPath path;    
    if (m_rect.isNull()) {
        m_shapePath = path;
        return;
    }
    if (m_nSpanAngle != 360 * 16) {
        path.moveTo(m_rect.center());
        path.arcTo(m_rect, m_nStartAngle / 16.0, m_nSpanAngle / 16.0);
    } else {
        path.addEllipse(m_rect);
    }

    m_shapePath = GraphicsShapeItem::qt_graphicsItem_shapeFromPath(q, path, m_pen);
    // 计算BoundingRect
    qreal pw = m_pen.style() == Qt::NoPen ? qreal(0) : m_pen.widthF();
    if (pw == 0.0 && m_nSpanAngle == 360 * 16)
        m_boundingRect = m_rect;
    else
        m_boundingRect = m_shapePath.controlPointRect();

}

GraphicsItemEllipse::GraphicsItemEllipse(GraphicsItemEllipsePrivate &dd, QGraphicsObject *parent)
    : GraphicsItemRect(dd, parent)
{

}

/*!
    Constructs a GraphicsEllipseItem using \a rect as the default rectangle.
    \a parent is passed to GraphicsShapeItem's constructor.

    \sa QGraphicsScene::addItem()
*/
GraphicsItemEllipse::GraphicsItemEllipse(const QRectF &rect, QGraphicsObject *parent)
    : GraphicsItemRect(*new GraphicsItemEllipsePrivate, parent)
{
    setRect(rect);
}

/*!
    \fn GraphicsEllipseItem::GraphicsEllipseItem(qreal x, qreal y, qreal width, qreal height, QGraphicsItem *parent)
    \since 4.3

    Constructs a GraphicsEllipseItem using the rectangle defined by (\a x, \a
    y) and the given \a width and \a height, as the default rectangle. \a
    parent is passed to GraphicsShapeItem's constructor.

    \sa QGraphicsScene::addItem()
*/
GraphicsItemEllipse::GraphicsItemEllipse(qreal x, qreal y, qreal w, qreal h, QGraphicsObject *parent)
    : GraphicsItemRect(*new GraphicsItemEllipsePrivate, parent)
{
    setRect(x,y,w,h);
}

GraphicsItemEllipse::GraphicsItemEllipse(const QRectF &rect, int startAngle, int nSpanAngle, QGraphicsObject *parent)
    : GraphicsItemRect(*new GraphicsItemEllipsePrivate, parent)
{

}



/*!
    Constructs a GraphicsEllipseItem. \a parent is passed to
    GraphicsShapeItem's constructor.

    \sa QGraphicsScene::addItem()
*/
GraphicsItemEllipse::GraphicsItemEllipse(QGraphicsObject *parent)
    : GraphicsItemRect(*new GraphicsItemEllipsePrivate, parent)
{
}

/*!
    Destroys the GraphicsEllipseItem.
*/
GraphicsItemEllipse::~GraphicsItemEllipse()
{
}

void GraphicsItemEllipse::setEllipse(const QRectF &rect, int startAngle, int spanAngle, bool update)
{
    Q_D(GraphicsItemEllipse);

    setRect(rect, false);

    setStartAngle(startAngle, false);

    setSpanAngle(spanAngle, false);

    if (update)
        updateShape();
}

/*!
    Returns the start angle for an ellipse segment in 16ths of a degree. This
    angle is used together with spanAngle() for representing an ellipse
    segment (a pie). By default, the start angle is 0.

    \sa setStartAngle(), spanAngle()
*/
int GraphicsItemEllipse::startAngle() const
{
    Q_D(const GraphicsItemEllipse);
    return d->m_nStartAngle;
}

/*!
    Sets the start angle for an ellipse segment to \a angle, which is in 16ths
    of a degree. This angle is used together with spanAngle() for representing
    an ellipse segment (a pie). By default, the start angle is 0.

    \sa startAngle(), setSpanAngle(), QPainter::drawPie()
*/
void GraphicsItemEllipse::setStartAngle(int angle, bool update)
{
    Q_D(GraphicsItemEllipse);
    if (angle == d->m_nStartAngle)
        return;

    d->m_nStartAngle = angle;

    if (update)
        updateShape();

    emit startAngleChanged(angle);
}

/*!
    Returns the span angle of an ellipse segment in 16ths of a degree. This
    angle is used together with startAngle() for representing an ellipse
    segment (a pie). By default, this function returns 5760 (360 * 16, a full
    ellipse).

    \sa setSpanAngle(), startAngle()
*/
int GraphicsItemEllipse::spanAngle() const
{
    Q_D(const GraphicsItemEllipse);
    return d->m_nSpanAngle;
}

/*!
    Sets the span angle for an ellipse segment to \a angle, which is in 16ths
    of a degree. This angle is used together with startAngle() to represent an
    ellipse segment (a pie). By default, the span angle is 5760 (360 * 16, a
    full ellipse).

    \sa spanAngle(), setStartAngle(), QPainter::drawPie()
*/
void GraphicsItemEllipse::setSpanAngle(int angle, bool update)
{
    Q_D(GraphicsItemEllipse);
    if (angle == d->m_nSpanAngle)
        return;

    d->m_nSpanAngle = angle;

    if (update)
        updateShape();

    emit spanAngleChanged(angle);

}


/*!
    \reimp
*/
void GraphicsItemEllipse::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                                 QWidget *widget)
{
    Q_D(GraphicsItemEllipse);
    Q_UNUSED(widget);
    painter->setPen(d->m_pen);
    painter->setBrush(d->m_brush);
    if ((d->m_nSpanAngle != 0) && (qAbs(d->m_nSpanAngle) % (360 * 16) == 0))
        painter->drawEllipse(d->m_rect);
    else
        painter->drawPie(d->m_rect, d->m_nStartAngle, d->m_nSpanAngle);

    if (option->state & QStyle::State_Selected)
        qt_graphicsItem_highlightSelected(this, painter, option);
}



/*!
    \reimp
*/
int GraphicsItemEllipse::type() const
{
    return Type;
}



}
