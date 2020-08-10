#ifndef GRAPHICSLINEITEM_H
#define GRAPHICSLINEITEM_H

#include "graphicsshapeslib_global.h"
#include "graphicsShapeItem.h"

namespace GraphicsShapes
{

class GraphicsItemLinePrivate;
class GRAPHICSSHAPESLIBSHARED_EXPORT GraphicsItemLine : public GraphicsShapeItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
protected:
    GraphicsItemLine(GraphicsItemLinePrivate &dd, QGraphicsObject *parent);
public:
    explicit GraphicsItemLine(QGraphicsObject *parent = Q_NULLPTR);
    explicit GraphicsItemLine(const QLineF &line, QGraphicsObject *parent = Q_NULLPTR);
    explicit GraphicsItemLine(qreal x1, qreal y1, qreal x2, qreal y2, QGraphicsObject *parent = Q_NULLPTR);
    ~GraphicsItemLine();
signals:
    void lineChanged(const QLineF& line);
public:
    QLineF line() const;

    void setP1(const QPointF& p, bool update = true);
    void setP2(const QPointF& p, bool update = true);
    void setLine(const QLineF &line, bool update = true);
    inline void setLine(qreal x1, qreal y1, qreal x2, qreal y2)
    { setLine(QLineF(x1, y1, x2, y2)); }


    enum { Type = ShapeLine };
    virtual  int type() const Q_DECL_OVERRIDE;

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR) Q_DECL_OVERRIDE;

private:
    Q_DISABLE_COPY(GraphicsItemLine)
    Q_DECLARE_PRIVATE_D(QGraphicsItem::d_ptr.data(), GraphicsItemLine)
};
}

#endif // GRAPHICSLINEITEM_H
