#include "graphicsRoiCircle.h"
#include <QGraphicsScene>

GraphicsRoiCircle::GraphicsRoiCircle(const QPointF &center, qreal radius, QGraphicsObject *parent)
    : GraphicsItemEllipse(QRectF(QPointF(center.x()-radius, center.y()-radius), QSizeF(radius*2, radius*2)), parent)
    , IRoi(this)
{
    init();
}

int GraphicsRoiCircle::type() const
{
    return Type;
}

void GraphicsRoiCircle::setCenter(const QPointF &center)
{

}

void GraphicsRoiCircle::setRadius(qreal radius)
{

}

void GraphicsRoiCircle::setCenterAndRadius(const QPointF &center, qreal radius)
{
    GraphicsItemEllipse::setRect(QRectF(QPointF(center.x()-radius, center.y()-radius), QSizeF(radius*2, radius*2)));
    setTransformOriginPoint(this->boundingRect().center());
    emit radiusChanged();
}

void GraphicsRoiCircle::setRect(const QRectF &rect)
{
    GraphicsItemEllipse::setRect(rect);
    setTransformOriginPoint(this->boundingRect().center());
    emit rectChanged();
}

void GraphicsRoiCircle::init()
{
    this->setFlag(ItemIsMovable);
    this->setFlag(ItemIsSelectable);
    this->setFlag(ItemIsFocusable);
    this->setCosmetic(true);
    this->setFiltersChildEvents(true);
    setTransformOriginPoint(this->boundingRect().center());

    m_anchorLeft   = new GraphicsAnchor(this, GraphicsAnchor::BordeLeft  , GraphicsAnchor::WholeMove);
    m_anchorRight  = new GraphicsAnchor(this, GraphicsAnchor::BordeRight , GraphicsAnchor::WholeMove);
    m_anchorTop    = new GraphicsAnchor(this, GraphicsAnchor::BordeTop   , GraphicsAnchor::WholeMove);
    m_anchorBottom = new GraphicsAnchor(this, GraphicsAnchor::BordeBottom, GraphicsAnchor::WholeMove);

    m_anchorTopLeft     = new GraphicsAnchor(this, GraphicsAnchor::BordeTopLeft    , GraphicsAnchor::WholeMove);
    m_anchorTopRight    = new GraphicsAnchor(this, GraphicsAnchor::BordeTopRight   , GraphicsAnchor::WholeMove);
    m_anchorBottomLeft  = new GraphicsAnchor(this, GraphicsAnchor::BordeBottomLeft , GraphicsAnchor::WholeMove);
    m_anchorBottomRight = new GraphicsAnchor(this, GraphicsAnchor::BordeBottomRight, GraphicsAnchor::WholeMove);

    m_anchorRotater = new GraphicsAnchor(this, GraphicsAnchor::OuterTop, GraphicsAnchor::Rotation, GraphicsAnchor::ShapeCircle);
    m_anchorRotater->setAntialiasing(true);
}

void GraphicsRoiCircle::setAnchorBordeColor(const QColor &color)
{
    m_colorAnchorBorde = color;
    QList<QGraphicsItem *> items = this->childItems();
    foreach (QGraphicsItem* item, items)
    {
        GraphicsAnchor* anchor = qgraphicsitem_cast<GraphicsAnchor*>(item);
        if (anchor)
            anchor->setPenColor(color);
    }
}

void GraphicsRoiCircle::setAnchorFillColor(const QColor &color)
{
    m_colorAnchorFill = color;
    QList<QGraphicsItem *> items = this->childItems();
    foreach (QGraphicsItem* item, items)
    {
        GraphicsAnchor* anchor = qgraphicsitem_cast<GraphicsAnchor*>(item);
        if (anchor)
            anchor->setBrushColor(color);
    }
}

void GraphicsRoiCircle::setRotatable(bool set)
{
    m_bRotatable = set;
    m_anchorRotater->setVisible(set);
}

void GraphicsRoiCircle::setResizable(bool set)
{
    m_bResizable = set;
    m_anchorLeft       ->setVisible(set);
    m_anchorRight      ->setVisible(set);
    m_anchorTop        ->setVisible(set);
    m_anchorBottom     ->setVisible(set);

    m_anchorTopLeft    ->setVisible(set);
    m_anchorTopRight   ->setVisible(set);
    m_anchorBottomLeft ->setVisible(set);
    m_anchorBottomRight->setVisible(set);
}

void GraphicsRoiCircle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    GraphicsItemEllipse::paint(painter, option, widget);

    paintCenter(painter, option, widget);
}
