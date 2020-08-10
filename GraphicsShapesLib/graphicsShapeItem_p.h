#ifndef GRAPHICSSHAPEITEMPRIVATE_P_H
#define GRAPHICSSHAPEITEMPRIVATE_P_H

#include "graphicsshapeslib_global.h"
#include <QtWidgets\private\qgraphicsitem_p.h>
#include "graphicsShapeItem.h"

namespace GraphicsShapes
{

class GRAPHICSSHAPESLIBSHARED_EXPORT GraphicsShapeItemPrivate : public QGraphicsItemPrivate
{
    Q_DECLARE_PUBLIC(GraphicsShapeItem)
public:
    inline GraphicsShapeItemPrivate()
    {
        m_pen.setCosmetic(true);
    }
protected:
    // 由派生类实现，更新shapePath
    virtual void updateShapePath() const = 0;
public:
    QBrush m_brush;
    QPen m_pen;

    // Cached bounding rectangle
    mutable QRectF m_boundingRect;
    mutable QPainterPath m_shapePath;
};

}

#endif // GRAPHICSSHAPEITEMPRIVATE_P_H
