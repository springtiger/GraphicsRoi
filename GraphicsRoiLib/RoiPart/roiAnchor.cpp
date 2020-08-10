#include "roiAnchor.h"
#include "roianchor_p.h"
#include <QDebug>

namespace GraphicsRoi
{

RoiAnchor::RoiAnchor(RoiAnchorPrivate &dd, QGraphicsObject *scaleObj, QGraphicsObject *parent)
    : GraphicsItemPoint(dd, scaleObj, parent)
{
    init();
}

int RoiAnchor::type() const
{
    return Type;
}

void RoiAnchor::init()
{
    Q_D(RoiAnchor);
    this->setAcceptHoverEvents(true);

    this->setFlag(ItemIsMovable  ); // 设置ItemIsMovable属性，以便响应鼠标移动，但是不会真正移动Anchor
    this->setFlag(ItemIsFocusable); // 设置ItemIsMovable属性，以便响应鼠标移动，但是不会真正移动Anchor
    this->setCursor(QCursor(Qt::ArrowCursor));
    this->setGraphicsEffect(d->m_effect);

}

void RoiAnchor::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    Q_D(RoiAnchor);
    d->m_effect->setEnabled(true);
    GraphicsItemPoint::hoverEnterEvent(event);
}

void RoiAnchor::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    Q_D(RoiAnchor);
    d->m_effect->setEnabled(false);
    GraphicsItemPoint::hoverLeaveEvent(event);
}

}
