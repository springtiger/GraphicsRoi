#include "cqchartview.h"
#include <QValueAxis>

CQChartView::CQChartView(QWidget *parent)
    : QChartView(parent)
    , IGraphicsChart(this)
{
    //this->setRenderHint(QPainter::Antialiasing);
    QChart* chart = new QChart();
    this->setChart(chart);
    QValueAxis *axisX = new QValueAxis;
    QValueAxis *axisY = new QValueAxis;

    axisX->setRange(-50, 50);
    axisY->setRange(-40, 40);
    axisX->setReverse(true);
    axisY->setReverse(true);
    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);

    m_seriesA = new QLineSeries;
    chart->addSeries(m_seriesA);
    m_seriesA->attachAxis(axisX);
    m_seriesA->attachAxis(axisY);

    m_seriesA->replace(QVector<QPointF>() <<QPointF(-40,-40)<<QPointF(-50,-30)<<QPointF(-30,-20)<<QPointF(-50,-10)<<QPointF(-20,0));
}

QAbstractSeries *CQChartView::currentSeries()
{
    return m_seriesA;
}
