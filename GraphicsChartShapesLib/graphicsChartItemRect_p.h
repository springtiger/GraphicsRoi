#ifndef GRAPHICSCHARTITEMRECT_P_H
#define GRAPHICSCHARTITEMRECT_P_H

#include "graphicsItemRect_p.h"
#include "graphicsChartItemRect.h"
#include "interfaceGraphicsChart.h"

class GraphicsChartItemRectPrivate : public GraphicsItemRectPrivate
{
    Q_DECLARE_PUBLIC(GraphicsChartItemRect)
public:
    inline GraphicsChartItemRectPrivate(IGraphicsChart *pChartInterface)
        : GraphicsItemRectPrivate()
        , m_pChartInterface(pChartInterface)
    {
        Q_ASSERT(m_pChartInterface != 0);
    }

public:
    virtual void updateShapePath() const override;
public:
    IGraphicsChart *m_pChartInterface;
    QRectF m_rectValue;
};

#endif // GRAPHICSCHARTITEMRECT_P_H
