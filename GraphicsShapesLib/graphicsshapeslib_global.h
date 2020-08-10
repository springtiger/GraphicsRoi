#ifndef GRAPHICSSHAPESLIB_GLOBAL_H
#define GRAPHICSSHAPESLIB_GLOBAL_H

#include <QtCore/qglobal.h>
#include <QGraphicsItem>

#if defined(GRAPHICSSHAPESLIB_LIBRARY)
#  define GRAPHICSSHAPESLIBSHARED_EXPORT Q_DECL_EXPORT
#else
#  define GRAPHICSSHAPESLIBSHARED_EXPORT Q_DECL_IMPORT
//#  define GRAPHICSSHAPESLIBSHARED_EXPORT
#endif

namespace GraphicsShapes
{
    Q_NAMESPACE

    enum ShapeType
    {
        ShapeRect = QGraphicsItem::UserType + 1,
        ShapePoint,
        ShapeEllipse,
        ShapeLine,
        ShapePath,
        ShapePolygon,
        ShapePixmap,
        ShapeSimpleText,
        UserShapeType,
    };

    Q_ENUM_NS(ShapeType);


}

#endif // GRAPHICSSHAPESLIB_GLOBAL_H
