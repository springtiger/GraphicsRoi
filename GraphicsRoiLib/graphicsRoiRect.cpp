#include "graphicsRoiRect.h"
#include <QDebug>
#include "eventFilterRoi.h"
#include <QGraphicsScene>
#include "graphicsItemLine.h"


GraphicsRoiRect::GraphicsRoiRect(const QRectF &rect, QGraphicsObject *parent)
    : GraphicsItemRect(rect, parent)
    , IRoi(this)
{
    init();
}

GraphicsRoiRect::GraphicsRoiRect(qreal x, qreal y, qreal w, qreal h, QGraphicsObject *parent)
    : GraphicsItemRect(x, y, w, h, parent)
    , IRoi(this)
{
    init();
}

GraphicsRoiRect::GraphicsRoiRect(const QPointF &center, const QSizeF &size, QGraphicsObject *parent)
    : GraphicsItemRect(QRectF(QPointF(center.x()-size.width()/2, center.y()-size.height()/2), size), parent)
    , IRoi(this)
{
    init();
}

GraphicsRoiRect::~GraphicsRoiRect()
{

}

int GraphicsRoiRect::type() const
{
    return Type;
}

void GraphicsRoiRect::setRect(const QRectF &rect)
{
    GraphicsItemRect::setRect(rect);
    setTransformOriginPoint(this->boundingRect().center());
    emit rectChanged();
}

void GraphicsRoiRect::setAnchorBordeColor(const QColor &color)
{
    m_clrAnchorBordeColor = color;
    QList<QGraphicsItem *> items = this->childItems();
    foreach (QGraphicsItem* item, items)
    {
        GraphicsAnchor* anchor = qgraphicsitem_cast<GraphicsAnchor*>(item);
        if (anchor)
            anchor->setPenColor(color);
    }
}

void GraphicsRoiRect::setAnchorFillColor(const QColor &color)
{
    m_clrAnchorFillColor = color;
    QList<QGraphicsItem *> items = this->childItems();
    foreach (QGraphicsItem* item, items)
    {
        GraphicsAnchor* anchor = qgraphicsitem_cast<GraphicsAnchor*>(item);
        if (anchor)
            anchor->setBrushColor(color);
    }
}

void GraphicsRoiRect::setRotatable(bool set)
{
    m_bRotatable = set;
    m_anchorRotater->setVisible(set);
}

void GraphicsRoiRect::setResizable(bool set)
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


void GraphicsRoiRect::init()
{
    this->setFlag(ItemIsMovable);
    this->setFlag(ItemIsSelectable);
    this->setFlag(ItemIsFocusable);
    this->setCosmetic(true);
    this->installEventFilter(new EventFilterRoi(scene())); // 右键菜单消息等
    this->setFiltersChildEvents(true);
    setTransformOriginPoint(this->boundingRect().center());

    m_anchorLeft        = new GraphicsAnchor(this, GraphicsAnchor::BordeLeft  );
    m_anchorRight       = new GraphicsAnchor(this, GraphicsAnchor::BordeRight );
    m_anchorTop         = new GraphicsAnchor(this, GraphicsAnchor::BordeTop   );
    m_anchorBottom      = new GraphicsAnchor(this, GraphicsAnchor::BordeBottom);
    m_anchorTopLeft     = new GraphicsAnchor(this, GraphicsAnchor::BordeTopLeft    );
    m_anchorTopRight    = new GraphicsAnchor(this, GraphicsAnchor::BordeTopRight   );
    m_anchorBottomLeft  = new GraphicsAnchor(this, GraphicsAnchor::BordeBottomLeft );
    m_anchorBottomRight = new GraphicsAnchor(this, GraphicsAnchor::BordeBottomRight);

    m_anchorRotater     = new GraphicsAnchor(this, GraphicsAnchor::OuterTop, GraphicsAnchor::Rotation, GraphicsAnchor::CircleShape);
    m_anchorRotater->setAntialiasing(true);

}

void GraphicsRoiRect::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    //painter->setRenderHint(QPainter::Antialiasing, this->rotation());
    GraphicsItemRect::paint(painter, option, widget);
}

void GraphicsRoiRect::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    return GraphicsItemRect::hoverEnterEvent(event);
}

void GraphicsRoiRect::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    return GraphicsItemRect::hoverLeaveEvent(event);
}

void GraphicsRoiRect::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
    return GraphicsItemRect::hoverMoveEvent(event);
}
