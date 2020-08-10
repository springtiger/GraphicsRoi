#include "graphicsRoiRect.h"
#include "graphicsRoiRect_p.h"
#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QtConcurrent>

#include "graphicsItemLine.h"

using namespace QtConcurrent;

namespace GraphicsRoi
{


GraphicsRoiRect::GraphicsRoiRect(GraphicsRoiRectPrivate &dd, QGraphicsObject *parent)
    : GraphicsItemRect(dd, parent)
    , IRoi(this)
{
    init(parent);
}

GraphicsRoiRect::GraphicsRoiRect(const QRectF &rect, QGraphicsObject *parent, AnchorMoveMode mode)
    : GraphicsItemRect(*new GraphicsRoiRectPrivate, parent)
    , IRoi(this)
{
    setRect(rect);
    init(parent, mode);
}

GraphicsRoiRect::GraphicsRoiRect(qreal x, qreal y, qreal w, qreal h, QGraphicsObject *parent, AnchorMoveMode mode)
    : GraphicsItemRect(*new GraphicsRoiRectPrivate, parent)
    , IRoi(this)
{
    setRect(x, y, w, h);
    init(parent, mode);
}

GraphicsRoiRect::GraphicsRoiRect(const QPointF &center, const QSizeF &size, QGraphicsObject *parent, AnchorMoveMode mode)
    : GraphicsItemRect(*new GraphicsRoiRectPrivate, parent)
    , IRoi(this)
{
    setRect(QRectF(QPointF(center.x()-size.width()/2, center.y()-size.height()/2), size));
    init(parent, mode);
}

GraphicsRoiRect::~GraphicsRoiRect()
{

}

int GraphicsRoiRect::type() const
{
    return Type;
}

void GraphicsRoiRect::setAnchorBordeColor(const QColor &color)
{
    m_colorAnchorBorde = color;
    QList<QGraphicsItem *> items = this->childItems();
    foreach (QGraphicsItem* item, items)
    {
        RectRoiAnchor* anchor = qgraphicsitem_cast<RectRoiAnchor*>(item);
        if (anchor)
            anchor->setPenColor(color);
    }
}

void GraphicsRoiRect::setAnchorFillColor(const QColor &color)
{
    m_colorAnchorFill = color;
    QList<QGraphicsItem *> items = this->childItems();
    foreach (QGraphicsItem* item, items)
    {
        RectRoiAnchor* anchor = qgraphicsitem_cast<RectRoiAnchor*>(item);
        if (anchor)
            anchor->setBrushColor(color);
    }
}

void GraphicsRoiRect::setResizeAnchorVisible(bool set)
{
    Q_D(GraphicsRoiRect);

    d->m_anchorLeft       ->setVisible(set);
    d->m_anchorRight      ->setVisible(set);
    d->m_anchorTop        ->setVisible(set);
    d->m_anchorBottom     ->setVisible(set);

    d->m_anchorTopLeft    ->setVisible(set);
    d->m_anchorTopRight   ->setVisible(set);
    d->m_anchorBottomLeft ->setVisible(set);
    d->m_anchorBottomRight->setVisible(set);
}

void GraphicsRoiRect::setRotateAnchorVisible(bool set)
{
    Q_D(GraphicsRoiRect);
    d->m_anchorRotater->setVisible(set);
}

void GraphicsRoiRect::setRotatable(bool set)
{
    Q_D(GraphicsRoiRect);

    m_bRotatable = set;

    setRotateAnchorVisible(set);
}

void GraphicsRoiRect::setResizable(bool set)
{
    Q_D(GraphicsRoiRect);
    m_bResizable = set;

    setResizeAnchorVisible( set);

}

void GraphicsRoiRect::setMovable(bool set)
{
    if (set)
        setFlags(flags() & ItemIsMovable & ItemIsSelectable & ItemIsFocusable);
    else
        setFlags(flags() & ~ItemIsMovable & ~ItemIsSelectable & ~ItemIsFocusable);
}

void GraphicsRoiRect::setCentreVisible(bool set)
{
    Q_D(GraphicsRoiRect);
    m_bCentreVisible = set;
    d->m_anchorCentre->setVisible(set);
}

void GraphicsRoiRect::setAnchorAutoHide(bool set)
{
    Q_D(GraphicsRoiRect);
    m_bAnchorAutoHide = set;

    setResizeAnchorVisible(!set);
    setRotateAnchorVisible(!set);
}




void GraphicsRoiRect::init(QGraphicsObject *parent, AnchorMoveMode mode )
{
    Q_D(GraphicsRoiRect);

    // 设置ROI可移动、可选中、可获得焦点
    this->setFlag(ItemIsMovable);
    this->setFlag(ItemIsSelectable);
    this->setFlag(ItemIsFocusable);

    // 设置画笔固定像素，不随缩放调整像素宽度
    this->setCosmetic(true);
    // 接收子项的事件
    this->setFiltersChildEvents(true);
    // 接受鼠标悬停事件
    setAcceptHoverEvents(true);
    // 设置ROI画刷颜色
    QColor clrblue(153, 204, 255, 200);
    this->setBrushColor(clrblue);
    //
    // 添加四边及四角的调节点
    d->m_anchorLeft        = new RectRoiAnchor(parent, this, BordeLeft  , mode);
    d->m_anchorRight       = new RectRoiAnchor(parent, this, BordeRight , mode);
    d->m_anchorTop         = new RectRoiAnchor(parent, this, BordeTop   , mode);
    d->m_anchorBottom      = new RectRoiAnchor(parent, this, BordeBottom, mode);
    d->m_anchorTopLeft     = new RectRoiAnchor(parent, this, BordeTopLeft    , mode);
    d->m_anchorTopRight    = new RectRoiAnchor(parent, this, BordeTopRight   , mode);
    d->m_anchorBottomLeft  = new RectRoiAnchor(parent, this, BordeBottomLeft , mode);
    d->m_anchorBottomRight = new RectRoiAnchor(parent, this, BordeBottomRight, mode);
    // 添加旋转调节点及中心点
    d->m_anchorRotater     = new RectRoiAnchor(parent, this, OuterTop, Rotation, GraphicsItemPoint::Circle);
    d->m_anchorCentre      = new RectRoiAnchor(parent, this, Center, FixedPos, GraphicsItemPoint::Circle, QSizeF(4,4));
    // 设置中心点颜色
    d->m_anchorCentre->setBrushColor(clrblue.darker());
    // 设置中心点不可选中，不可移动
    d->m_anchorCentre->setFlags(d->m_anchorCentre->flags() & ~ItemIsFocusable & ~ItemIsMovable & ~ItemIsSelectable);

    setRotatable(true);
    setResizable(true);
    setCentreVisible(true);
    setAnchorAutoHide(true);
}

void GraphicsRoiRect::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_D(GraphicsRoiRect);
    // 原始矩形
    QPainterPath srcPath;
    srcPath.addRect(this->boundingRect());
    // 将裁剪不显示的矩形
    QPainterPath clipPath = QPainterPath();
    if (d->m_anchorLeft       ->isVisible()) clipPath.addRect(d->m_anchorLeft       ->rect()  );
    if (d->m_anchorRight      ->isVisible()) clipPath.addRect(d->m_anchorRight      ->rect()  );
    if (d->m_anchorTop        ->isVisible()) clipPath.addRect(d->m_anchorTop        ->rect()  );
    if (d->m_anchorBottom     ->isVisible()) clipPath.addRect(d->m_anchorBottom     ->rect()  );
    if (d->m_anchorTopLeft    ->isVisible()) clipPath.addRect(d->m_anchorTopLeft    ->rect()  );
    if (d->m_anchorTopRight   ->isVisible()) clipPath.addRect(d->m_anchorTopRight   ->rect()  );
    if (d->m_anchorBottomLeft ->isVisible()) clipPath.addRect(d->m_anchorBottomLeft ->rect()  );
    if (d->m_anchorBottomRight->isVisible()) clipPath.addRect(d->m_anchorBottomRight->rect()  );
    // 设置裁剪不显示
    painter->setClipPath(srcPath.subtracted(clipPath));

    GraphicsItemRect::paint(painter, option, widget);
}

void GraphicsRoiRect::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    Q_D(GraphicsRoiRect);
    if (m_bAnchorAutoHide)
    {   // 移出时，取消AutoHide
        d->m_animationAutoHide.stop();

        setResizeAnchorVisible(m_bResizable);
        setRotateAnchorVisible(m_bRotatable);
    }

    return GraphicsItemRect::hoverEnterEvent(event);
}

void GraphicsRoiRect::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    Q_D(GraphicsRoiRect);
    // 需要隐藏，则执行隐藏
    if (m_bAnchorAutoHide)
    {
        // 创建
        connect(&d->m_animationAutoHide, &QPauseAnimation::finished, this, [=]()
        {
                setResizeAnchorVisible(false);
                setRotateAnchorVisible(false);

                disconnect(&d->m_animationAutoHide, &QPauseAnimation::finished, 0, 0);
        });
        // 运行指定时间长度后退出。
        d->m_animationAutoHide.setDuration(300);
        d->m_animationAutoHide.start();
    }

    return GraphicsItemRect::hoverLeaveEvent(event);
}

void GraphicsRoiRect::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
    return GraphicsItemRect::hoverMoveEvent(event);
}

void GraphicsRoiRect::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    GraphicsItemRect::mouseMoveEvent(event);
}

void GraphicsRoiRect::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit pressed();
    GraphicsItemRect::mousePressEvent(event);
}


}
