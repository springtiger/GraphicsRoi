#ifndef GRAPHICSCHARTITEMLINESEGMENT_P_H
#define GRAPHICSCHARTITEMLINESEGMENT_P_H

#include "graphicsItemLine_p.h"
#include "graphicsChartItemLineSegment.h"
#include "interfaceGraphicsChart.h"


class GraphicsChartItemLineSegmentPrivate : public GraphicsItemLinePrivate
{
    Q_DECLARE_PUBLIC(GraphicsChartItemLineSegment)
public:
    inline GraphicsChartItemLineSegmentPrivate(IGraphicsChart *pChartInterface)
        : GraphicsItemLinePrivate()
        , m_pChartInterface(pChartInterface)
    {
        Q_ASSERT(m_pChartInterface != 0);
    }

public:
    virtual void updateShapePath() const override;
public:
    IGraphicsChart *m_pChartInterface;
    QLineF m_valueLine;
};

#endif // GRAPHICSCHARTITEMLINESEGMENT_P_H
