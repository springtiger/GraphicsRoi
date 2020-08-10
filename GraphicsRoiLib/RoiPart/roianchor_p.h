#ifndef ROIANCHOR_P_H
#define ROIANCHOR_P_H
#include "graphicsroilib_global.h"
#include "graphicsItemPoint_p.h"
#include <QGraphicsDropShadowEffect>

namespace GraphicsRoi
{

class GRAPHICSROILIBSHARED_EXPORT RoiAnchorPrivate : public GraphicsItemPointPrivate
{
    Q_DECLARE_PUBLIC(RoiAnchor)
public :
    RoiAnchorPrivate()
        : GraphicsItemPointPrivate()
        , m_OuterPosOffset(13)
    {
        m_effect = new QGraphicsDropShadowEffect;
        m_effect->setBlurRadius(15);
        m_effect->setOffset(0);
        m_effect->setColor(Qt::red);
        m_effect->setEnabled(false);
    }

public:
    QGraphicsDropShadowEffect *m_effect;
    int m_OuterPosOffset; // 旋转点位置距Rect边界的距离
};

}
#endif // ROIANCHOR_P_H
