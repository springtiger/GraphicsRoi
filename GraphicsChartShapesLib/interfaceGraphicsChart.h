#ifndef INTERFACECHARTITEM_H
#define INTERFACECHARTITEM_H

#include <QObject>
#include <QChartView>
#include <QChart>
#include <QXYSeries>
#include <QValueAxis>

#include "graphicsShapeItem.h"

QT_CHARTS_USE_NAMESPACE

class IGraphicsChart
{
public:
    IGraphicsChart(QChartView* pChartView)
        : m_pChartView(pChartView)
    {
        Q_ASSERT(m_pChartView!= 0);
    }

public:
    QChartView *chartView()
    {
        return m_pChartView;
    }

    virtual QAbstractSeries* currentSeries() = 0;

    void init(GraphicsShapeItem *shapeItem)
    {
        QChart *pChart = m_pChartView->chart();
        QXYSeries *pSeries = qobject_cast<QXYSeries *>(currentSeries());
        QValueAxis *pAxisX = qobject_cast<QValueAxis *>(pChart->axisX(pSeries));
        QValueAxis *pAxisY = qobject_cast<QValueAxis *>(pChart->axisY(pSeries));

        QObject::connect(pChart, &QChart::plotAreaChanged,  shapeItem, &GraphicsShapeItem::updateShape);
        QObject::connect(pAxisX, &QValueAxis::rangeChanged, shapeItem, &GraphicsShapeItem::updateShape);
        QObject::connect(pAxisY, &QValueAxis::rangeChanged, shapeItem, &GraphicsShapeItem::updateShape);
    }

protected:
    QChartView *m_pChartView;
};


QT_BEGIN_NAMESPACE

#define IGraphicsChart_iid "org.qt-project.Qt.GraphicsChartShapeslib.IGraphicsChart"

Q_DECLARE_INTERFACE(IGraphicsChart, IGraphicsChart_iid)
QT_END_NAMESPACE

#endif // INTERFACECHARTITEM_H
