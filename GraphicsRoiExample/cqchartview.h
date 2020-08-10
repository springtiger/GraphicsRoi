#ifndef CQCHARTVIEW_H
#define CQCHARTVIEW_H

#include "interfaceGraphicsChart.h"
#include <QChartView>
#include <QLineSeries>

class CQChartView : public QChartView, public IGraphicsChart
{
    Q_OBJECT
    Q_INTERFACES(IGraphicsChart)
public:
    CQChartView(QWidget *parent = Q_NULLPTR);
public:
    virtual QAbstractSeries* currentSeries();
private:
    QLineSeries *m_seriesA;
    QLineSeries *m_seriesB;
};

#endif // CQCHARTVIEW_H
