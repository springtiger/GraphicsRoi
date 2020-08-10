#ifndef GRAPHICSCHARTITEMPOLYGON_P_H
#define GRAPHICSCHARTITEMPOLYGON_P_H

#include "graphicsItemPolygon_p.h"
#include "graphicsChartItemPolygon.h"
#include "interfaceGraphicsChart.h"


class GraphicsChartItemPolygonPrivate : public GraphicsItemPolygonPrivate
{
    Q_DECLARE_PUBLIC(GraphicsChartItemPolygon)
public:
    inline GraphicsChartItemPolygonPrivate(IGraphicsChart *pChartInterface)
        : GraphicsItemPolygonPrivate()
        , m_pChartInterface(pChartInterface)
    {
        Q_ASSERT(m_pChartInterface != 0);
    }

public:
    virtual void updateShapePath() const override;
public:
    IGraphicsChart *m_pChartInterface;
    QPolygonF m_valuePolygon;
};

#endif // GRAPHICSCHARTITEMPOLYGON_P_H
