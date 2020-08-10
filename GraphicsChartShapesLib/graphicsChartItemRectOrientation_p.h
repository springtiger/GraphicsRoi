#ifndef GRAPHICSCHARTITEMRECTORIENTATION_P_H
#define GRAPHICSCHARTITEMRECTORIENTATION_P_H

#include "graphicsItemRect_p.h"
#include "graphicsChartItemRect.h"
#include "interfaceGraphicsChart.h"

class GraphicsChartItemRectOrientationPrivate : public GraphicsItemRectPrivate
{
    Q_DECLARE_PUBLIC(GraphicsChartItemRectOrientation)
public:
    inline GraphicsChartItemRectOrientationPrivate(IGraphicsChart *pChartInterface)
        : GraphicsItemRectPrivate()
        , m_pChartInterface(pChartInterface)
    {
        Q_ASSERT(m_pChartInterface != 0);
    }

public:
    virtual void updateShapePath() const override;
public:
    IGraphicsChart *m_pChartInterface;
    Qt::Orientation m_orientation;
    qreal m_fValueA;
    qreal m_fValueB;
};

#endif // GRAPHICSCHARTITEMRECTORIENTATION_P_H
