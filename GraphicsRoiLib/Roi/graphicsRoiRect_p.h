#ifndef GRAPHICSROIRECT_P_H
#define GRAPHICSROIRECT_P_H

#include "graphicsroilib_global.h"
#include "graphicsRoiRect.h"
#include "graphicsItemRect_p.h"

#include <QPainterPath>

#include "RoiPart/rectRoiAnchor.h"
#include "backgroundsleeper.h"
#include <QPauseAnimation>

namespace GraphicsRoi
{

class GRAPHICSROILIBSHARED_EXPORT GraphicsRoiRectPrivate : public GraphicsItemRectPrivate
{
    Q_DECLARE_PUBLIC(GraphicsRoiRect)
public:
    GraphicsRoiRectPrivate()
        : GraphicsItemRectPrivate()
    {

    }

public:
    RectRoiAnchor *m_anchorLeft  ;
    RectRoiAnchor *m_anchorRight ;
    RectRoiAnchor *m_anchorTop   ;
    RectRoiAnchor *m_anchorBottom;

    RectRoiAnchor *m_anchorTopLeft    ;
    RectRoiAnchor *m_anchorTopRight   ;
    RectRoiAnchor *m_anchorBottomLeft ;
    RectRoiAnchor *m_anchorBottomRight;

    RectRoiAnchor *m_anchorRotater    ;
    RectRoiAnchor *m_anchorCentre     ;

    QPainterPath m_clipPath;

    QPauseAnimation m_animationAutoHide;
};

}

#endif // GRAPHICSROIRECT_P_H
