#include "graphicsAnchor.h"
#include "graphicsAnchor_p.h"

#include "graphicsRoiRect.h"
#include "graphicsRoiEllipse.h"
#include "graphicsRoiCircle.h"
#include "graphicsRoiRing.h"
#include "graphicsRoiPolygon.h"
#include "graphicsShapeItem.h"

#include <QDebug>
#include <QtMath>
#include <QtGui\private\qbezier_p.h>
#include <QtGui\private\qstroker_p.h>

#define OuterOffset 15

qreal qt_t_for_arc_angle(qreal angle)
{
    if (qFuzzyIsNull(angle))
        return 0;

    if (qFuzzyCompare(angle, qreal(90)))
        return 1;

    qreal radians = qDegreesToRadians(angle);
    qreal cosAngle = qCos(radians);
    qreal sinAngle = qSin(radians);

    // initial guess
    qreal tc = angle / 90;
    // do some iterations of newton's method to approximate cosAngle
    // finds the zero of the function b.pointAt(tc).x() - cosAngle
    tc -= ((((2-3*QT_PATH_KAPPA) * tc + 3*(QT_PATH_KAPPA-1)) * tc) * tc + 1 - cosAngle) // value
         / (((6-9*QT_PATH_KAPPA) * tc + 6*(QT_PATH_KAPPA-1)) * tc); // derivative
    tc -= ((((2-3*QT_PATH_KAPPA) * tc + 3*(QT_PATH_KAPPA-1)) * tc) * tc + 1 - cosAngle) // value
         / (((6-9*QT_PATH_KAPPA) * tc + 6*(QT_PATH_KAPPA-1)) * tc); // derivative

    // initial guess
    qreal ts = tc;
    // do some iterations of newton's method to approximate sinAngle
    // finds the zero of the function b.pointAt(tc).y() - sinAngle
    ts -= ((((3*QT_PATH_KAPPA-2) * ts -  6*QT_PATH_KAPPA + 3) * ts + 3*QT_PATH_KAPPA) * ts - sinAngle)
         / (((9*QT_PATH_KAPPA-6) * ts + 12*QT_PATH_KAPPA - 6) * ts + 3*QT_PATH_KAPPA);
    ts -= ((((3*QT_PATH_KAPPA-2) * ts -  6*QT_PATH_KAPPA + 3) * ts + 3*QT_PATH_KAPPA) * ts - sinAngle)
         / (((9*QT_PATH_KAPPA-6) * ts + 12*QT_PATH_KAPPA - 6) * ts + 3*QT_PATH_KAPPA);

    // use the average of the t that best approximates cosAngle
    // and the t that best approximates sinAngle
    qreal t = 0.5 * (tc + ts);

#if 0
    printf("angle: %f, t: %f\n", angle, t);
    qreal a, b, c, d;
    bezierCoefficients(t, a, b, c, d);
    printf("cosAngle: %.10f, value: %.10f\n", cosAngle, a + b + c * QT_PATH_KAPPA);
    printf("sinAngle: %.10f, value: %.10f\n", sinAngle, b * QT_PATH_KAPPA + c + d);
#endif

    return t;
}

void qt_find_ellipse_coords(const QRectF &r, qreal angle, qreal length,
                            QPointF* startPoint, QPointF *endPoint)
{
    if (r.isNull()) {
        if (startPoint)
            *startPoint = QPointF();
        if (endPoint)
            *endPoint = QPointF();
        return;
    }

    qreal w2 = r.width() / 2;
    qreal h2 = r.height() / 2;

    qreal angles[2] = { angle, angle + length };
    QPointF *points[2] = { startPoint, endPoint };

    for (int i = 0; i < 2; ++i) {
        if (!points[i])
            continue;

        qreal theta = angles[i] - 360 * qFloor(angles[i] / 360);
        qreal t = theta / 90;
        // truncate
        int quadrant = int(t);
        t -= quadrant;

        t = qt_t_for_arc_angle(90 * t);

        // swap x and y?
        if (quadrant & 1)
            t = 1 - t;

        qreal a, b, c, d;
        QBezier::coefficients(t, a, b, c, d);
        QPointF p(a + b + c*QT_PATH_KAPPA, d + c + b*QT_PATH_KAPPA);

        // left quadrants
        if (quadrant == 1 || quadrant == 2)
            p.rx() = -p.x();

        // top quadrants
        if (quadrant == 0 || quadrant == 1)
            p.ry() = -p.y();

        *points[i] = r.center() + QPointF(w2 * p.x(), h2 * p.y());
    }
}


void GraphicsAnchorPrivate::updateShapePath() const
{
    Q_Q(const GraphicsItemRect);

    QTransform t;

    t.rotate(q->parentObject()->rotation());

    QPainterPath path;
    path.addPolygon(t.map(m_rect));

    m_shapePath = GraphicsShapeItem::qt_graphicsItem_shapeFromPath(path, m_pen);
}

GraphicsAnchor::GraphicsAnchor(GraphicsShapeItem *parent)
    : GraphicsItemRect(*new GraphicsAnchorPrivate, parent)
{
    init();
}

GraphicsAnchor::GraphicsAnchor(GraphicsShapeItem *parent, GraphicsAnchor::AnchorPositionFlag pos, ActionMode actionMode, GraphicsAnchor::ShapeStyle shapeStyle, const QSizeF &size)
    : GraphicsItemRect(*new GraphicsAnchorPrivate, parent)
{
    Q_D(GraphicsAnchor);
    d->m_positionFlag = pos;
    d->m_shapeStyle = shapeStyle;
    d->m_actionMode = actionMode;

    setRect(QRectF(QPointF(-size.width()/2, -size.height()/2), size));

    init();
}

GraphicsAnchor::GraphicsAnchor(GraphicsShapeItem *parent, int polyIndex, GraphicsAnchor::ShapeStyle shapeStyle, const QSizeF &size)
    : GraphicsItemRect(*new GraphicsAnchorPrivate, parent)
{
    Q_D(GraphicsAnchor);
    d->m_positionFlag = PolyPos;
    d->m_shapeStyle = shapeStyle;
    d->m_actionMode = PolyPointMove;
    d->m_polyIndex = polyIndex;

    setRect(QRectF(QPointF(-size.width()/2, -size.height()/2), size));

    init();
}

GraphicsAnchor::~GraphicsAnchor()
{
}

int GraphicsAnchor::type() const
{
    return Type;
}

void GraphicsAnchor::setAntialiasing(bool antialiasing)
{
    Q_D(GraphicsAnchor);
    d->m_antialiasing = antialiasing;
    update();
}

int GraphicsAnchor::polyIndex()
{
    Q_D(GraphicsAnchor);
    return d->m_polyIndex;
}

void GraphicsAnchor::setPolyIndex(int index)
{
    Q_D(GraphicsAnchor);
    d->m_polyIndex = index;
}




//!
//! \brief GraphicsAnchor::GraphicsAnchor internal
//! \param dd
//! \param parent
//!
GraphicsAnchor::GraphicsAnchor(GraphicsAnchorPrivate &dd, QGraphicsObject *parent)
    : GraphicsItemRect(dd, parent)
{

}

void GraphicsAnchor::init()
{
    Q_D(GraphicsAnchor);
    //qDebug() << "GraphicsAnchor::init";
    // 初始化Anchor基本属性
    this->setFlag(ItemIsMovable  ); // 设置ItemIsMovable属性，以便响应鼠标移动，但是不会真正移动Anchor
    this->setFlag(ItemIsFocusable); // 设置ItemIsMovable属性，以便响应鼠标移动，但是不会真正移动Anchor
    this->setFlag(ItemIgnoresTransformations);
    this->setAcceptHoverEvents(true);
    this->setCosmetic(true); // 线宽始终为1像素
    this->setCursor(QCursor(Qt::ArrowCursor));
    this->setZValue(1.0);
    this->setGraphicsEffect(d->m_effect);

    updateAnchorPos(); // 更新Anchor位置
    //qDebug() << (parentItem()->type()) << "updateAnchorPos finished";


    // 点击Achor选中Roi
    connect(this, &GraphicsAnchor::mousePressed, this, [this](){
        QList<QGraphicsItem *> items = scene()->selectedItems();
        foreach (QGraphicsItem *item, items) {
            item->setSelected(false);
        }
        parentObject()->setSelected(true); });
    // ROI已旋转,将导致所有Anchor需要旋转,在Painter中实现painter->rotate(parentItem()->rotation());
    connect(parentObject(), &QGraphicsObject::rotationChanged, this, [this]()
    {
        this->updateShape();
    });
    // ROI的父Item,即图片,已缩放,旋转点位置需要调整,使之不受缩放影响
    connect(parentObject()->parentObject(), &QGraphicsObject::scaleChanged, this, [this](){
        updateAnchorPos();
    });


    GraphicsRoiRect *rectRoi = 0;
    GraphicsRoiEllipse *ellipseRoi = 0;
    GraphicsRoiCircle *circleRoi = 0;

    switch (parentObject()->type())
    {
    case GraphicsRoiRect::Type:
        rectRoi = qgraphicsitem_cast<GraphicsRoiRect*>(parentObject());
        connect(rectRoi, &GraphicsRoiRect::rectChanged, this, &GraphicsAnchor::updateAnchorPos);
        break;
    case GraphicsRoiEllipse::Type:
        ellipseRoi = qgraphicsitem_cast<GraphicsRoiEllipse*>(parentObject());
        connect(ellipseRoi, &GraphicsRoiEllipse::rectChanged, this, &GraphicsAnchor::updateAnchorPos);
        break;
    case GraphicsRoiCircle::Type:
        circleRoi = qgraphicsitem_cast<GraphicsRoiCircle*>(parentObject());
        connect(circleRoi, &GraphicsRoiCircle::rectChanged, this, &GraphicsAnchor::updateAnchorPos);
        break;
    case GraphicsRoiPolygon::Type:
        break;
    default:
        break;
    }
}

void GraphicsAnchor::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit mousePressed();
    GraphicsItemRect::mousePressEvent(event);
}

void GraphicsAnchor::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    emit mouseDoubleClicked();
    GraphicsItemRect::mousePressEvent(event);
}

void GraphicsAnchor::updateAnchorPos()
{
    Q_D(GraphicsAnchor);
    if (this->parentObject() == 0)
		return;
	
    QGraphicsItem *parent = this->parentObject();
	if (parent == 0)
		return;

    QRectF bordeRect;
    QPointF angleStart;
    QPointF angleEnd;
    GraphicsRoiRect    *rectRoi    = 0;
    GraphicsRoiEllipse *ellipseRoi = 0;
    GraphicsRoiCircle  *circleRoi  = 0;
    GraphicsRoiPolygon *polygonRoi = 0;

    switch (parent->type())
    {
    case GraphicsRoiRect::Type:
        rectRoi = qgraphicsitem_cast<GraphicsRoiRect*>(parent);
        bordeRect = rectRoi->rect();
        break;
    case GraphicsRoiEllipse::Type:
        ellipseRoi = qgraphicsitem_cast<GraphicsRoiEllipse*>(parent);
        bordeRect = ellipseRoi->rect();
        {
            int angle = 0;
            int span  = 0;
            QRectF halfBordeRect;
            QSizeF size = bordeRect.size()/4;
            halfBordeRect = bordeRect.marginsRemoved(QMarginsF(size.width(), size.height(), size.width(), size.height()));
            angle = ellipseRoi->startAngle() / 16.0;
            span  = ellipseRoi->spanAngle() / 16.0;
            qt_find_ellipse_coords(halfBordeRect, angle, span, &angleStart, &angleEnd);
        }
        break;
    case GraphicsRoiCircle::Type:
        circleRoi = qgraphicsitem_cast<GraphicsRoiCircle*>(parent);
        bordeRect = circleRoi->rect();
        {
//            int angle = 0;
//            int span  = 0;
//            QRectF halfBordeRect;
//            QSizeF size = bordeRect.size()/4;
//            halfBordeRect = bordeRect.marginsRemoved(QMarginsF(size.width(), size.height(), size.width(), size.height()));
//            angle = circleRoi->startAngle();
//            span  = circleRoi->spanAngle() ;
//            qt_find_ellipse_coords(halfBordeRect, angle, span, &angleStart, &angleEnd);
        }
        break;
    case GraphicsRoiPolygon::Type:
        polygonRoi = qgraphicsitem_cast<GraphicsRoiPolygon*>(parent);
        break;
    default:
        break;
    }


    QRectF bordeRectNormalized = bordeRect.normalized();
    qreal offsetLen = 0.0;
    // 为旋转点计算偏移距离，不受缩放影响，所以mapFromScene
    if (!bordeRect.isNull())
        offsetLen =  QLineF( this->mapFromScene(0, 0), this->mapFromScene(0, OuterOffset))
                    .length();


    switch (d->m_positionFlag)
    {
    case BordeLeft:
        this->setPos(QPointF(bordeRect.left(), bordeRect.center().y()));
        break;
    case BordeRight:
        this->setPos(QPointF(bordeRect.right(), bordeRect.center().y()));
        break;
    case BordeTop:
        this->setPos(QPointF(bordeRect.center().x(), bordeRect.top()));
        break;
    case BordeBottom:
        this->setPos(QPointF(bordeRect.center().x(), bordeRect.bottom()));
        break;
    case BordeTopLeft:
        this->setPos(bordeRect.topLeft());
        break;
    case BordeTopRight:
        this->setPos(bordeRect.topRight());
        break;
    case BordeBottomLeft:
        this->setPos(bordeRect.bottomLeft());
        break;
    case BordeBottomRight:
        this->setPos(bordeRect.bottomRight());
        break;
    case OuterLeft  :
        this->setPos(QPointF(bordeRectNormalized.left()-offsetLen, bordeRectNormalized.center().y()));
        break;
    case OuterRight :
        this->setPos(QPointF(bordeRectNormalized.right()+offsetLen, bordeRectNormalized.center().y()));
        break;
    case OuterTop   :
        this->setPos(QPointF(bordeRectNormalized.center().x(), bordeRectNormalized.top()- offsetLen));
        break;
    case OuterBottom:
        this->setPos(QPointF(bordeRectNormalized.center().x(), bordeRectNormalized.bottom()+offsetLen));
        break;
    case ByAngleStart:
        this->setPos(angleStart);
        break;
    case ByAngleSpan:
        this->setPos(angleEnd);
        break;
    case Center:
        this->setPos(this->parentObject()->boundingRect().center());
        break;
    case PolyPos:
        this->setPos(polygonRoi->polygon()[d->m_polyIndex]);
        break;
    default:
        break;
    }
}

void GraphicsAnchor::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    Q_D(GraphicsAnchor);

    QGraphicsObject *parent = this->parentObject();

    if (parent == 0)
        return ;

    QPointF offset = parent->mapFromScene(event->scenePos()) - parent->mapFromScene(event->lastScenePos());

    QRectF bordeRect;
    qreal rotationSpan = 0;
    GraphicsRoiRect    *rectRoi = 0;
    GraphicsRoiEllipse *ellipseRoi = 0;
    GraphicsRoiCircle  *circleRoi = 0;
    GraphicsRoiPolygon *polygonRoi = 0;

    switch (parent->type())
    {
    case GraphicsRoiRect::Type:
        rectRoi    = qgraphicsitem_cast<GraphicsRoiRect*>(parent);
        bordeRect = rectRoi->rect();
        break;
    case GraphicsRoiEllipse::Type:
        ellipseRoi = qgraphicsitem_cast<GraphicsRoiEllipse*>(parent);
        bordeRect = ellipseRoi->rect();
        break;
    case GraphicsRoiCircle::Type:
        circleRoi = qgraphicsitem_cast<GraphicsRoiCircle*>(parent);
        bordeRect = circleRoi->rect();
        break;
    case GraphicsRoiPolygon::Type:
        polygonRoi = qgraphicsitem_cast<GraphicsRoiPolygon*>(parent);
        break;
    default:
        break;
    }


    QPointF FixToPos;
    QPointF posAfterSet;
    QPointF posOffset;
    qreal realOffset = 0.0;
    switch (d->m_actionMode)
    {
    case EdgeMove:
        switch (d->m_positionFlag)
        {
        case InnerLeft:
        case OuterLeft:
        case BordeLeft:
            bordeRect.setLeft(bordeRect.left() + offset.x());
            break;
        case InnerRight:
        case OuterRight:
        case BordeRight:
            bordeRect.setRight(bordeRect.right() + offset.x());
            break;
        case InnerTop:
        case OuterTop:
        case BordeTop:
            bordeRect.setTop(bordeRect.top() + offset.y());
            break;
        case InnerBottom:
        case OuterBottom:
        case BordeBottom:
            bordeRect.setBottom(bordeRect.bottom() + offset.y());
            break;
        case BordeTopLeft:
            bordeRect.setTopLeft(bordeRect.topLeft()+offset);
            break;
        case BordeTopRight:
            bordeRect.setTopRight(bordeRect.topRight()+offset);
            break;
        case BordeBottomLeft:
            bordeRect.setBottomLeft(bordeRect.bottomLeft()+offset);
            break;
        case BordeBottomRight:
            bordeRect.setBottomRight(bordeRect.bottomRight()+offset);
            break;
        default:
            break;
        }

        switch (parent->type())
        {
        case GraphicsRoiRect::Type:
            FixToPos = rectRoi->mapToParent(QPointF());
            rectRoi->setRect(bordeRect);
            posAfterSet = rectRoi->mapToParent(QPointF());
            posOffset = FixToPos - posAfterSet;
            rectRoi->setPos(rectRoi->pos() + posOffset);
            break;
        case GraphicsRoiEllipse::Type:
            FixToPos = ellipseRoi->mapToParent(QPointF());
            ellipseRoi->setRect(bordeRect);
            posAfterSet = ellipseRoi->mapToParent(QPointF());
            posOffset = FixToPos - posAfterSet;
            ellipseRoi->setPos(ellipseRoi->pos() + posOffset);
            break;
        case GraphicsRoiCircle::Type:
            FixToPos = circleRoi->mapToParent(QPointF());
            circleRoi->setRect(bordeRect);
            posAfterSet = circleRoi->mapToParent(QPointF());
            posOffset = FixToPos - posAfterSet;
            circleRoi->setPos(circleRoi->pos() + posOffset);
            break;
        default:
            break;
        }
        break;
    case OppositeMove:
        switch (d->m_positionFlag)
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

        switch (parent->type())
        {
        case GraphicsRoiRect::Type:
            FixToPos = rectRoi->mapToParent(QPointF());
            rectRoi->setRect(bordeRect);
            posAfterSet = rectRoi->mapToParent(QPointF());
            posOffset = FixToPos - posAfterSet;
            rectRoi->setPos(rectRoi->pos() + posOffset);
            break;
        case GraphicsRoiEllipse::Type:
            FixToPos = ellipseRoi->mapToParent(QPointF());
            ellipseRoi->setRect(bordeRect);
            posAfterSet = ellipseRoi->mapToParent(QPointF());
            posOffset = FixToPos - posAfterSet;
            ellipseRoi->setPos(ellipseRoi->pos() + posOffset);
            break;
        case GraphicsRoiCircle::Type:
            FixToPos = circleRoi->mapToParent(QPointF());
            circleRoi->setRect(bordeRect);
            posAfterSet = circleRoi->mapToParent(QPointF());
            posOffset = FixToPos - posAfterSet;
            circleRoi->setPos(circleRoi->pos() + posOffset);
            break;
        default:
            break;
        }

        break;
    case WholeMove:
        switch (d->m_positionFlag)
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

        switch (parent->type())
        {
        case GraphicsRoiRect::Type:
            FixToPos = rectRoi->mapToParent(QPointF());
            rectRoi->setRect(bordeRect);
            posAfterSet = rectRoi->mapToParent(QPointF());
            posOffset = FixToPos - posAfterSet;
            rectRoi->setPos(rectRoi->pos() + posOffset);
            break;
        case GraphicsRoiEllipse::Type:
            FixToPos = ellipseRoi->mapToParent(QPointF());
            ellipseRoi->setRect(bordeRect);
            posAfterSet = ellipseRoi->mapToParent(QPointF());
            posOffset = FixToPos - posAfterSet;
            ellipseRoi->setPos(ellipseRoi->pos() + posOffset);
            break;
        case GraphicsRoiCircle::Type:
            FixToPos = circleRoi->mapToParent(QPointF());
            circleRoi->setRect(bordeRect);
            posAfterSet = circleRoi->mapToParent(QPointF());
            posOffset = FixToPos - posAfterSet;
            circleRoi->setPos(circleRoi->pos() + posOffset);
            break;
        default:
            break;
        }
        break;
    case Rotation:
        switch (d->m_positionFlag)
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
            rotationSpan = QLineF(parent->mapToScene(parent->boundingRect().center()), event->scenePos()).angleTo(QLineF(parent->mapToScene(parent->boundingRect().center()), event->lastScenePos()))  ;
            parent->setRotation(parent->rotation() + rotationSpan);
            break;
        default:
            break;
        }
        break;
    case PolyPointMove:
        polygonRoi->updatePos(d->m_polyIndex, polygonRoi->polygon()[d->m_polyIndex]+offset);
        this->setPos(polygonRoi->polygon()[d->m_polyIndex]);
        break;
    default:
        break;
    }


}

void GraphicsAnchor::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    Q_D(GraphicsAnchor);

    d->m_effect->setEnabled(true);
    GraphicsItemRect::hoverEnterEvent(event);
}

void GraphicsAnchor::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    Q_D(GraphicsAnchor);

    d->m_effect->setEnabled(false);
    GraphicsItemRect::hoverLeaveEvent(event);
}

void GraphicsAnchor::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_D(GraphicsAnchor);
    Q_UNUSED(widget);

    painter->save();
    painter->rotate(parentObject()->rotation());
    painter->setPen(d->m_pen);
    painter->setBrush(d->m_brush);

    switch (d->m_shapeStyle)
    {
    case ShapeRectangle:
        painter->setRenderHint(QPainter::Antialiasing, parentObject()->rotation());
        painter->drawRect(d->m_rect);
        break;
    case ShapeCircle:
        painter->setRenderHint(QPainter::Antialiasing, true);
        painter->drawEllipse(d->m_rect);
        break;
    default:
        break;
    }

    if (option->state & QStyle::State_Selected)
        qt_graphicsItem_highlightSelected(this, painter, option);

    painter->restore();
}

