#include "rectRoiAnchor.h"
#include "rectRoiAnchor_p.h"
#include "graphicsItemRect.h"

using namespace GraphicsShapes;

namespace GraphicsRoi
{

RectRoiAnchor::RectRoiAnchor(RectRoiAnchorPrivate &dd, QGraphicsObject *scaleObj, GraphicsItemRect *parent)
    : RoiAnchor(dd, scaleObj, parent)
{
    init(parent);

}

RectRoiAnchor::RectRoiAnchor(QGraphicsObject *scaleObj, GraphicsItemRect *parent)
    : RoiAnchor(*new RectRoiAnchorPrivate, scaleObj, parent)
{
    init(parent);
}

RectRoiAnchor::RectRoiAnchor(QGraphicsObject *scaleObj, GraphicsItemRect *parent, AnchorPosType pos, AnchorMoveMode moveMode, GraphicsItemPoint::ShapeStyle shapeStyle, const QSizeF &size)
    : RoiAnchor(*new RectRoiAnchorPrivate, scaleObj, parent)
{
    init(parent);
    setAnchor(scaleObj, pos, moveMode, shapeStyle, size);
}

int RectRoiAnchor::type() const
{
    return Type;
}

void RectRoiAnchor::setAnchor(QGraphicsObject *scaleObj, AnchorPosType pos, AnchorMoveMode moveMode, GraphicsItemPoint::ShapeStyle shapeStyle, const QSizeF &size)
{
    setAnchorPos(scaleObj, pos, false);
    setAnchorMoveMode(moveMode);
    setShapeStyle(shapeStyle, false);
    setSize(size, false);

    updateShape();
}

void RectRoiAnchor::setAnchorPos(QGraphicsObject *scaleObj, AnchorPosType pos, bool update)
{
    Q_D(RectRoiAnchor);
    if (pos == d->m_posType)
        return;

    d->m_posType = pos;

    if (pos >= OuterLeft && pos <= OuterBottom){
        connect(scaleObj, &QGraphicsObject::scaleChanged, this, [this](){ updateAnchorPos(); });
    }

    updateAnchorPos(update);

    emit anchorPosTypeChanged(d->m_posType);
}

void RectRoiAnchor::setAnchorMoveMode(AnchorMoveMode moveMode, bool update)
{
    Q_D(RectRoiAnchor);
    if (moveMode == d->m_moveMode)
        return;

    d->m_moveMode = moveMode;

    if (update)
        updateShape();

    emit anchorMoveModeChanged(d->m_moveMode);
}

void RectRoiAnchor::updateAnchorPos(bool update)
{
    Q_D(RectRoiAnchor);

    GraphicsItemRect *parentItem = qobject_cast<GraphicsItemRect*>(this->parentObject());
    Q_ASSERT(parentItem != 0);

    QRectF bordeRect = parentItem->rect();
    QRectF bordeRectN = bordeRect.normalized();
    float offsetLen =  QLineF( this->mapFromScene(0, 0), this->mapFromScene(0, d->m_OuterPosOffset)).length();

    QPointF pos = bordeRect.center();

    switch (d->m_posType)
    {
    case BordeLeft    :
        pos.setX(bordeRect.left());
        break;
    case BordeRight   :
        pos.setX(bordeRect.right());
        break;
    case BordeTop     :
        pos.setY(bordeRect.top());
        break;
    case BordeBottom  :
        pos.setY(bordeRect.bottom());
        break;

    case BordeTopLeft    :
        pos = bordeRect.topLeft();
        break;
    case BordeTopRight   :
        pos = bordeRect.topRight();
        break;
    case BordeBottomLeft :
        pos = bordeRect.bottomLeft();
        break;
    case BordeBottomRight:
        pos = bordeRect.bottomRight();
        break;

    case OuterLeft  :
        pos.setX(bordeRectN.left()-offsetLen);
        break;
    case OuterRight :
        pos.setX(bordeRectN.right()+offsetLen);
        break;
    case OuterTop   :
        pos.setY(bordeRectN.top()-offsetLen);
        break;
    case OuterBottom:
        pos.setY(bordeRectN.bottom()+offsetLen);
        break;

    case Center:
        //pos = bordeRect.center();
        break;
    default:
        break;
    }

    setPos(pos, update);
}

void RectRoiAnchor::init(GraphicsItemRect *parent)
{
    connect(parent, &GraphicsItemRect::rectChanged, this, [this](){this->updateAnchorPos();});
}

void RectRoiAnchor::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    Q_D(RectRoiAnchor);
    GraphicsItemRect *parentItem = qobject_cast<GraphicsItemRect*>(this->parentObject());
    Q_ASSERT(parentItem != 0);

//    QPointF offset = parentItem->mapFromScene(event->scenePos()) - parentItem->mapFromScene(event->lastScenePos());
    QPointF offset = event->pos() - event->lastPos();
    QRectF bordeRect = parentItem->rect();

    switch (d->m_moveMode)
    {
    case FixedPos:
        break;
    case EdgeMove:
        // 设置bordeRect移动后的位置
        switch (d->m_posType)
        {
        case BordeLeft       :
        case InnerLeft       :
        case OuterLeft       :
            bordeRect.setLeft(bordeRect.left() + offset.x());
            break;
        case BordeRight      :
        case InnerRight      :
        case OuterRight      :
            bordeRect.setRight(bordeRect.right() + offset.x());
            break;
        case BordeTop        :
        case InnerTop        :
        case OuterTop        :
            bordeRect.setTop(bordeRect.top() + offset.y());
            break;
        case BordeBottom     :
        case InnerBottom     :
        case OuterBottom     :
            bordeRect.setBottom(bordeRect.bottom() + offset.y());
            break;
        case BordeTopLeft    :
            bordeRect.setTopLeft(bordeRect.topLeft()+offset);
            break;
        case BordeTopRight   :
            bordeRect.setTopRight(bordeRect.topRight()+offset);
            break;
        case BordeBottomLeft :
            bordeRect.setBottomLeft(bordeRect.bottomLeft()+offset);
            break;
        case BordeBottomRight:
            bordeRect.setBottomRight(bordeRect.bottomRight()+offset);
            break;
        case Center          :
            break;
        case EllipseStart    :
            break;
        case EllipseStop     :
            break;
        default:
            break;
        }

        break;
    case OppositeMove:
        switch (d->m_posType)
        {
        case InnerLeft:
        case OuterLeft:
        case BordeLeft:
            bordeRect.setLeft(bordeRect.left() + offset.x());
            bordeRect.setRight(bordeRect.right() - offset.x());
            break;
        case InnerRight:
        case OuterRight:
        case BordeRight:
            bordeRect.setRight(bordeRect.right() + offset.x());
            bordeRect.setLeft(bordeRect.left() - offset.x());
            break;
        case InnerTop:
        case OuterTop:
        case BordeTop:
            bordeRect.setTop(bordeRect.top() + offset.y());
            bordeRect.setBottom(bordeRect.bottom() - offset.y());
            break;
        case InnerBottom:
        case OuterBottom:
        case BordeBottom:
            bordeRect.setBottom(bordeRect.bottom() + offset.y());
            bordeRect.setTop(bordeRect.top() - offset.y());
            break;
        case BordeTopLeft:
            bordeRect.setTopLeft(bordeRect.topLeft()+offset);
            bordeRect.setBottomRight(bordeRect.bottomRight()-offset);
            break;
        case BordeTopRight:
            bordeRect.setTopRight(bordeRect.topRight()+offset);
            bordeRect.setBottomLeft(bordeRect.bottomLeft()-offset);
            break;
        case BordeBottomLeft:
            bordeRect.setBottomLeft(bordeRect.bottomLeft()+offset);
            bordeRect.setTopRight(bordeRect.topRight()-offset);
            break;
        case BordeBottomRight:
            bordeRect.setBottomRight(bordeRect.bottomRight()+offset);
            bordeRect.setTopLeft(bordeRect.topLeft()-offset);
            break;
        default:
            break;
        }

        break;
    case WholeMove:
    {
        float realOffset = 0;
        switch (d->m_posType)
        {
        case InnerLeft:
        case OuterLeft:
        case BordeLeft:
            realOffset = offset.x();
            break;
        case InnerRight:
        case OuterRight:
        case BordeRight:
            realOffset = -offset.x();
            break;
        case InnerTop:
        case OuterTop:
        case BordeTop:
            realOffset = offset.y();
            break;
        case InnerBottom:
        case OuterBottom:
        case BordeBottom:
            realOffset = -offset.y();
            break;
        case BordeTopLeft:
            realOffset = qAbs(offset.x()) > qAbs(offset.y()) ? offset.x() : offset.y();
            break;
        case BordeTopRight:
            realOffset = qAbs(offset.x()) > qAbs(offset.y()) ? -offset.x() : offset.y();
            break;
        case BordeBottomLeft:
            realOffset = qAbs(offset.x()) > qAbs(offset.y()) ? offset.x() : -offset.y();
            break;
        case BordeBottomRight:
            realOffset = qAbs(offset.x()) > qAbs(offset.y()) ? -offset.x() : -offset.y();
            break;
        default:
            break;
        }
        bordeRect = QRectF( QPointF(bordeRect.left() + realOffset
                           , bordeRect.top() + realOffset)
                           , QPointF(bordeRect.right() - realOffset
                           , bordeRect.bottom() - realOffset));
    }
        break;
    case Rotation:
        switch (d->m_posType)
        {
        case InnerLeft:
        case OuterLeft:
        case BordeLeft:
        case InnerRight:
        case OuterRight:
        case BordeRight:
        case InnerTop:
        case OuterTop:
        case BordeTop:
        case InnerBottom:
        case OuterBottom:
        case BordeBottom:
        case BordeTopLeft:
        case BordeTopRight:
        case BordeBottomLeft:
        case BordeBottomRight:
        {
            qreal rotationSpan = QLineF(parentItem->mapToScene(parentItem->boundingRect().center()), event->scenePos())
                    .angleTo(QLineF(parentItem->mapToScene(parentItem->boundingRect().center()), event->lastScenePos()))  ;
            parentItem->setRotation(parentItem->rotation() + rotationSpan);
        }
        break;
        default:
            break;
        }

        break;
    default:
        break;
    }

    switch (d->m_moveMode) {
    case FixedPos:
        break;
    case EdgeMove:
    case OppositeMove:
    case WholeMove:
        // 应用到
        {
            QPointF FixToPos = parentItem->mapToParent(QPointF(0,0));
            parentItem->setRect(bordeRect);
            QPointF posAfterSet = parentItem->mapToParent(QPointF(0,0));
            QPointF posOffset = FixToPos - posAfterSet;
            parentItem->setPos(parentItem->pos() + posOffset);
        }
        break;
    case Rotation:
        break;
    default:
        break;
    }
}



}
