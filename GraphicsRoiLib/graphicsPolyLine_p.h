#ifndef GRAPHICSPOLYLINE_P_H
#define GRAPHICSPOLYLINE_P_H
#include "graphicsItemLine_p.h"
#include "graphicsPolyLine.h"

class GraphicsPolyLinePrivate : public GraphicsItemLinePrivate
{
    Q_DECLARE_PUBLIC(GraphicsPolyLine)
public:
    inline GraphicsPolyLinePrivate()
        : GraphicsItemLinePrivate()
    {

    }

public:
    virtual void updateShapePath() const override;
};

#endif // GRAPHICSPOLYLINE_P_H
