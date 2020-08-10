#ifndef GRAPHICSELLIPSEITEM_P_H
#define GRAPHICSELLIPSEITEM_P_H

#include "graphicsshapeslib_global.h"
#include "graphicsItemEllipse.h"
#include "graphicsItemRect_p.h"

namespace GraphicsShapes
{

/*!
    \class GraphicsEllipseItem
    \brief The GraphicsEllipseItem class provides an ellipse item that you
    can add to a QGraphicsScene.
    \since 4.2
    \ingroup graphicsview-api
    \inmodule QtWidgets

    GraphicsEllipseItem respresents an ellipse with a fill and an outline,
    and you can also use it for ellipse segments (see startAngle(),
    spanAngle()).

    \table
        \row
            \li \inlineimage graphicsview-ellipseitem.png
            \li \inlineimage graphicsview-ellipseitem-pie.png
    \endtable

    To set the item's ellipse, pass a QRectF to GraphicsEllipseItem's
    constructor, or call setRect(). The rect() function returns the
    current ellipse geometry.

    GraphicsEllipseItem uses the rect and the pen width to provide a
    reasonable implementation of boundingRect(), shape(), and contains(). The
    paint() function draws the ellipse using the item's associated pen and
    brush, which you can set by calling setPen() and setBrush().

    \sa QGraphicsPathItem, QGraphicsRectItem, QGraphicsPolygonItem,
    QGraphicsTextItem, QGraphicsLineItem, QGraphicsPixmapItem, {Graphics
    View Framework}
*/

class GRAPHICSSHAPESLIBSHARED_EXPORT GraphicsItemEllipsePrivate : public GraphicsItemRectPrivate
{
    Q_DECLARE_PUBLIC(GraphicsItemEllipse)
public:
    inline GraphicsItemEllipsePrivate()
        : GraphicsItemRectPrivate()
        , m_nStartAngle(0), m_nSpanAngle(360 * 16)
    { }

protected:
    virtual void updateShapePath() const override;

public:
    mutable int m_nStartAngle; //StartAngle和SpanAngle必须在1/16度内指定，即一个完整的圆等于5760(16*360)。正值为逆时针方向，负值为顺时针方向。
    mutable int m_nSpanAngle;
};

} // namespace

#endif // GRAPHICSELLIPSEITEM_P_H

