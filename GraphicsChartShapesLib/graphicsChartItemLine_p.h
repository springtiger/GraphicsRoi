#ifndef GRAPHICSCHARTITEMLINE_P_H
#define GRAPHICSCHARTITEMLINE_P_H

#include "graphicsItemLine_p.h"
#include "graphicsChartItemLine.h"
#include "interfaceGraphicsChart.h"


class GraphicsChartItemLinePrivate : public GraphicsItemLinePrivate
{
    Q_DECLARE_PUBLIC(GraphicsChartItemLine)
public:
    inline GraphicsChartItemLinePrivate(IGraphicsChart *pChartInterface)
        : GraphicsItemLinePrivate()
        , m_pChartInterface(pChartInterface)
    {
        Q_ASSERT(m_pChartInterface != 0);
    }

public:
    virtual void updateShapePath() const override;
public:
    IGraphicsChart *m_pChartInterface;
    qreal m_fValueA;
    qreal m_fValueB;
    qreal m_fValueC;
};

#endif // GRAPHICSCHARTITEMLINE_P_H
