#include "graphicsRoiEllipse.h"
#include <QDebug>
#include <QGraphicsScene>

GraphicsRoiEllipse::GraphicsRoiEllipse(const QRectF &rect, QGraphicsObject *parent)
    : GraphicsItemEllipse(rect, parent)
    , IRoi(this)
{
    init();
}

GraphicsRoiEllipse::GraphicsRoiEllipse(qreal x, qreal y, qreal w, qreal h, QGraphicsObject *parent)
    : GraphicsItemEllipse(x, y, w, h, parent)
    , IRoi(this)
{
    init();
}

GraphicsRoiEllipse::GraphicsRoiEllipse(const QPointF &center, const QSizeF &size, QGraphicsObject *parent)
    : GraphicsItemEllipse(QRectF(QPointF(center.x()-size.width()/2, center.y()-size.height()/2), size), parent)
    , IRoi(this)
{
    init();
}

int GraphicsRoiEllipse::type() const
{
    return Type;
}

void GraphicsRoiEllipse::init()
{
    this->setFlag(ItemIsMovable);
    this->setFlag(ItemIsSelectable);
    this->setFlag(ItemIsFocusable);
    this->setCosmetic(true);
    this->setFiltersChildEvents(true);

    m_anchorLeft   = new GraphicsAnchor(this, GraphicsAnchor::BordeLeft  , GraphicsAnchor::OppositeMove);
    m_anchorRight  = new GraphicsAnchor(this, GraphicsAnchor::BordeRight , GraphicsAnchor::OppositeMove);
    m_anchorTop    = new GraphicsAnchor(this, GraphicsAnchor::BordeTop   , GraphicsAnchor::OppositeMove);
    m_anchorBottom = new GraphicsAnchor(this, GraphicsAnchor::BordeBottom, GraphicsAnchor::OppositeMove);

    m_anchorTopLeft     = new GraphicsAnchor(this, GraphicsAnchor::BordeTopLeft    , GraphicsAnchor::OppositeMove);
    m_anchorTopRight    = new GraphicsAnchor(this, GraphicsAnchor::BordeTopRight   , GraphicsAnchor::OppositeMove);
    m_anchorBottomLeft  = new GraphicsAnchor(this, GraphicsAnchor::BordeBottomLeft , GraphicsAnchor::OppositeMove);
    m_anchorBottomRight = new GraphicsAnchor(this, GraphicsAnchor::BordeBottomRight, GraphicsAnchor::OppositeMove);

    m_anchorRotater = new GraphicsAnchor(this, GraphicsAnchor::OuterTop, GraphicsAnchor::Rotation, GraphicsAnchor::ShapeCircle);

    m_anchorAngleStart = new GraphicsAnchor(this, GraphicsAnchor::ByAngleStart, GraphicsAnchor::AngleSpan);
    m_anchorAngleSpan  = new GraphicsAnchor(this, GraphicsAnchor::ByAngleSpan , GraphicsAnchor::AngleSpan);
}

void GraphicsRoiEllipse::setAnchorBordeColor(const QColor &color)
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

void GraphicsRoiEllipse::setAnchorFillColor(const QColor &color)
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

void GraphicsRoiEllipse::setRotatable(bool set)
{
    m_bRotatable = set;
    m_anchorRotater->setVisible(set);
}

void GraphicsRoiEllipse::setResizable(bool set)
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

void GraphicsRoiEllipse::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setRenderHint(QPainter::Antialiasing);
    GraphicsItemEllipse::paint(painter, option, widget);

}
