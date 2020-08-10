#ifndef GRAPHICSRINGROI_H
#define GRAPHICSRINGROI_H

#include "graphicsroilib_global.h"
#include "graphicsItemRect.h"
#include "graphicsAnchor.h"

class GRAPHICSROILIBSHARED_EXPORT GraphicsRoiRing : public GraphicsItemRect
{
public:
    GraphicsRoiRing();
private:

private:
    friend class GraphicsAnchor;
};

#endif // GRAPHICSRINGROI_H
