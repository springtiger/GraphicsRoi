/*
 * //StartAngle和SpanAngle必须在1/16度内指定，即一个完整的圆等于5760(16*360)。正值为逆时针方向，负值为顺时针方向。
 *
 */

#ifndef GRAPHICSELLIPSEITEM_H
#define GRAPHICSELLIPSEITEM_H

#include "graphicsshapeslib_global.h"
#include "graphicsItemRect.h"

namespace GraphicsShapes
{

class GraphicsItemEllipsePrivate;
class GRAPHICSSHAPESLIBSHARED_EXPORT GraphicsItemEllipse : public GraphicsItemRect
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
protected:
    GraphicsItemEllipse(GraphicsItemEllipsePrivate &dd, QGraphicsObject *parent);
public:
    explicit GraphicsItemEllipse(QGraphicsObject *parent = Q_NULLPTR);
    explicit GraphicsItemEllipse(const QRectF &rect, QGraphicsObject *parent = Q_NULLPTR);
    explicit GraphicsItemEllipse(qreal x, qreal y, qreal w, qreal h, QGraphicsObject *parent = Q_NULLPTR);
    explicit GraphicsItemEllipse(const QRectF &rect, int startAngle, int nSpanAngle, QGraphicsObject *parent = Q_NULLPTR);
    ~GraphicsItemEllipse();
signals:
    void startAngleChanged(int angle);
    void spanAngleChanged(int angle);
public:
    //StartAngle和SpanAngle必须在1/16度内指定，即一个完整的圆等于5760(16*360)。正值为逆时针方向，负值为顺时针方向。
    void setEllipse(const QRectF &rect, int startAngle, int spanAngle, bool update = true);

    int startAngle() const;
    void setStartAngle(int angle, bool update = true);

    int spanAngle() const;
    void setSpanAngle(int angle, bool update = true);

    enum { Type = ShapeEllipse };
    virtual int type() const Q_DECL_OVERRIDE;

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR) Q_DECL_OVERRIDE;

private:
    Q_DISABLE_COPY(GraphicsItemEllipse)
    Q_DECLARE_PRIVATE_D(QGraphicsItem::d_ptr.data(), GraphicsItemEllipse)
};


}

#endif // GRAPHICSELLIPSEITEM_H
