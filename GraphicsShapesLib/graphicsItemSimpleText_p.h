#ifndef GRAPHICSSIMPLETEXTITEM_P_H
#define GRAPHICSSIMPLETEXTITEM_P_H

#include "graphicsShapeItem_p.h"
#include "graphicsItemSimpleText.h"
#include "graphicsshapeslib_global.h"

namespace GraphicsShapes
{

class GRAPHICSSHAPESLIBSHARED_EXPORT GraphicsItemSimpleTextPrivate : public GraphicsShapeItemPrivate
{
    Q_DECLARE_PUBLIC(GraphicsItemSimpleText)
public:
    inline GraphicsItemSimpleTextPrivate()
        : GraphicsShapeItemPrivate()
    {
        m_pen.setStyle(Qt::NoPen);

    }
public:
    virtual void updateShapePath() const override;
public:
    QString text;
    QFont font;
};

}
#endif // GRAPHICSSIMPLETEXTITEM_P_H
