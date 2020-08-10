#include "graphicsLayoutItemSimpleText.h"

namespace GraphicsShapes
{

GraphicsLayoutItemSimpleText::GraphicsLayoutItemSimpleText(QGraphicsObject *parent)
    : GraphicsItemSimpleText(parent)
    , QGraphicsLayoutItem(0, false)
{
    setGraphicsItem(this);
    setOwnedByLayout(true);

}

GraphicsLayoutItemSimpleText::GraphicsLayoutItemSimpleText(const QString &text, QGraphicsObject *parent)
    : GraphicsItemSimpleText(parent)
    , QGraphicsLayoutItem(0, false)
{
    setGraphicsItem(this);
    setOwnedByLayout(true);
    setText(text);
}

GraphicsLayoutItemSimpleText::~GraphicsLayoutItemSimpleText()
{

}

void GraphicsLayoutItemSimpleText::setText(const QString &text)
{
    GraphicsItemSimpleText::setText(text);
    this->updateGeometry();
}

QSizeF GraphicsLayoutItemSimpleText::sizeHint(Qt::SizeHint which, const QSizeF &constraint) const
{
    Q_UNUSED(which)
    Q_UNUSED(constraint)

    return this->boundingRect().size();
}

void GraphicsLayoutItemSimpleText::setGeometry(const QRectF &rect)
{
    this->setPos(rect.topLeft());
}

}
