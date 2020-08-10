#ifndef RECTROIANCHOR_P_H
#define RECTROIANCHOR_P_H

#include "graphicsroilib_global.h"
#include "roiAnchor_p.h"
#include "rectRoiAnchor.h"

namespace GraphicsRoi
{

class GRAPHICSROILIBSHARED_EXPORT RectRoiAnchorPrivate : public RoiAnchorPrivate
{
    Q_DECLARE_PUBLIC(RectRoiAnchor)
public:
    RectRoiAnchorPrivate()
        : RoiAnchorPrivate()
        , m_posType(Unknow)
        , m_moveMode(EdgeMove)
    {

    }
public:
    AnchorPosType m_posType;
    AnchorMoveMode m_moveMode;
};

}
#endif // RECTROIANCHOR_P_H
