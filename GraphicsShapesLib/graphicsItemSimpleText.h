#ifndef GRAPHICSSIMPLETEXTITEM_H
#define GRAPHICSSIMPLETEXTITEM_H

#include "graphicsShapeItem.h"
#include "graphicsshapeslib_global.h"

namespace GraphicsShapes
{

class GraphicsItemSimpleTextPrivate;
class GRAPHICSSHAPESLIBSHARED_EXPORT GraphicsItemSimpleText : public GraphicsShapeItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
protected:
    GraphicsItemSimpleText(GraphicsItemSimpleTextPrivate &dd, QGraphicsObject *parent);
public:
    explicit GraphicsItemSimpleText(QGraphicsObject *parent = Q_NULLPTR);
    explicit GraphicsItemSimpleText(const QString &text, QGraphicsObject *parent = Q_NULLPTR);
    ~GraphicsItemSimpleText();

signals:
    void textChanged(const QString & text);
    void fontChanged(const QFont& font);
public:
    void setText(const QString &text);
    QString text() const;

    void setFont(const QFont &font);
    QFont font() const;

    enum { Type = ShapeSimpleText };
    virtual int type() const Q_DECL_OVERRIDE;

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;

private:
    Q_DISABLE_COPY(GraphicsItemSimpleText)
    Q_DECLARE_PRIVATE_D(QGraphicsItem::d_ptr.data(), GraphicsItemSimpleText)
};

}
#endif // GRAPHICSSIMPLETEXTITEM_H
