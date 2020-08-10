#ifndef GRAPHICSCHARTITEMELLIPSE_P_H
#define GRAPHICSCHARTITEMELLIPSE_P_H

#include "graphicsItemEllipse_p.h"
#include "graphicsChartItemEllipse.h"
#include "interfaceGraphicsChart.h"


class GraphicsChartItemEllipsePrivate : public GraphicsItemEllipsePrivate
{
    Q_DECLARE_PUBLIC(GraphicsChartItemEllipse)
public:
    inline GraphicsChartItemEllipsePrivate(IGraphicsChart *pChartInterface)
        : GraphicsItemEllipsePrivate()
        , m_pChartInterface(pChartInterface)
    {
        Q_ASSERT(m_pChartInterface != 0);
    }

public:
    virtual void updateShapePath() const override;
public:
    IGraphicsChart *m_pChartInterface;

    mutable QRectF m_valueRect;
};

#endif // GRAPHICSCHARTITEMELLIPSE_P_H
