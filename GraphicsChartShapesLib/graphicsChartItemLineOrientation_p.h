#ifndef GRAPHICSCHARTITEMLINEORIENTATION_P_H
#define GRAPHICSCHARTITEMLINEORIENTATION_P_H


#include "graphicsItemLine_p.h"
#include "graphicsChartItemLineOrientation.h"
#include "interfaceGraphicsChart.h"


class GraphicsChartItemLineOrientationPrivate : public GraphicsItemLinePrivate
{
    Q_DECLARE_PUBLIC(GraphicsChartItemLineOrientation)
public:
    inline GraphicsChartItemLineOrientationPrivate(IGraphicsChart *pChartInterface)
        : GraphicsItemLinePrivate()
        , m_pChartInterface(pChartInterface)
    {
        Q_ASSERT(m_pChartInterface != 0);
    }

public:
    virtual void updateShapePath() const override;
public:
    IGraphicsChart *m_pChartInterface;
    Qt::Orientation m_orientation;
    qreal m_fValue;
};


#endif // GRAPHICSCHARTITEMLINEORIENTATION_P_H
