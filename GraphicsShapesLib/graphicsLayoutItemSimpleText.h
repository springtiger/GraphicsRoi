#ifndef LAYOUTGRAPHICSSIMPLETEXTITEM_H
#define LAYOUTGRAPHICSSIMPLETEXTITEM_H
#include "graphicsshapeslib_global.h"
#include "graphicsItemSimpleText.h"
#include <QGraphicsLayoutItem>

namespace GraphicsShapes
{

class GRAPHICSSHAPESLIBSHARED_EXPORT GraphicsLayoutItemSimpleText : public GraphicsItemSimpleText, public QGraphicsLayoutItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem QGraphicsLayoutItem)
public:
    explicit GraphicsLayoutItemSimpleText(QGraphicsObject *parent = Q_NULLPTR);
    explicit GraphicsLayoutItemSimpleText(const QString &text, QGraphicsObject *parent = Q_NULLPTR);
    ~GraphicsLayoutItemSimpleText();
    void setText(const QString& text);
protected:
    virtual QSizeF sizeHint(Qt::SizeHint which, const QSizeF &constraint = QSizeF()) const ;
    virtual void setGeometry(const QRectF &rect);
};

}
#endif // LAYOUTGRAPHICSSIMPLETEXTITEM_H
