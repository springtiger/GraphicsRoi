#ifndef GRAPHICSROILIB_GLOBAL_H
#define GRAPHICSROILIB_GLOBAL_H

#include <QtCore/qglobal.h>
#include <qobjectdefs.h>
#include "graphicsshapeslib_global.h"

using namespace GraphicsShapes;

#if defined(GRAPHICSROILIB_LIBRARY)
#  define GRAPHICSROILIBSHARED_EXPORT Q_DECL_EXPORT
#else
#  define GRAPHICSROILIBSHARED_EXPORT Q_DECL_IMPORT
#endif

namespace GraphicsRoi
{
    Q_NAMESPACE

    enum AnchorPosType
    {
        Unknow,

        BordeLeft        = 0x1   , // 边界框
        BordeRight       = 0x2   , // 边界框
        BordeTop         = 0x4   , // 边界框
        BordeBottom      = 0x8   , // 边界框

        BordeTopLeft     = 0x10  ,
        BordeTopRight    = 0x20  ,
        BordeBottomLeft  = 0x40  ,
        BordeBottomRight = 0x80  ,

        InnerLeft        = 0x100 , // 内边界框, 如Ring的内环
        InnerRight       = 0x200 , // 内边界框
        InnerTop         = 0x400 , // 内边界框
        InnerBottom      = 0x800 , // 内边界框

        OuterLeft        = 0x1000, // 边界框外部, 如旋转点
        OuterRight       = 0x2000, // 边界框外部
        OuterTop         = 0x4000, // 边界框外部
        OuterBottom      = 0x8000, // 边界框外部

        Center           ,
        EllipseStart     ,
        EllipseStop      ,
        PolygonPos       ,
    };
    Q_ENUM_NS(AnchorPosType);

    enum AnchorMoveMode
    {
        FixedPos,
        EdgeMove,
        OppositeMove ,
        WholeMove ,
        Rotation  ,
    };

    Q_ENUM_NS(AnchorMoveMode);

    enum RoiType
    {
        RectRoi = UserShapeType + 1,
        EllipseRoi,
        RingRoi,
        PolygonRoi,
        UserRoiPartType,

    };
    Q_ENUM_NS(RoiType);

    enum RoiPartType
    {
        Anchor     = UserRoiPartType,
        RectAnchor ,
        EllipseAnchor,
        RingAnchor,
        PolygonAnchor,
    };
    Q_ENUM_NS(RoiPartType);

};

#endif // GRAPHICSROILIB_GLOBAL_H
