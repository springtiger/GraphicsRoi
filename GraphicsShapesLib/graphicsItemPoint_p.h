#ifndef GRAPHICSITEMANCHOR_P_H
#define GRAPHICSITEMANCHOR_P_H

#include "graphicsshapeslib_global.h"
#include "graphicsItemRect_p.h"
#include "graphicsItemPoint.h"

namespace GraphicsShapes
{

class GRAPHICSSHAPESLIBSHARED_EXPORT GraphicsItemPointPrivate : public GraphicsItemRectPrivate
{
    Q_DECLARE_PUBLIC(GraphicsItemPoint)
public:
    inline GraphicsItemPointPrivate()
        : GraphicsItemRectPrivate()
        , m_shapeStyle(GraphicsItemPoint::Rectangle)
    {

    }

protected:
    virtual void updateShapePath()const override;
    QPainterPath calcPainterPath(const QRectF& r) const;
public:
    mutable QPointF m_point;
    mutable QSizeF m_size;
    GraphicsItemPoint::ShapeStyle m_shapeStyle;
};
}

#endif // GRAPHICSITEMANCHOR_P_H
