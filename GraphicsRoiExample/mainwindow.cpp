#include "mainwindow.h"
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QResizeEvent>

#include <QMenuBar>
#include <QDebug>
#include <QGraphicsRectItem>
#include <QSplitter>
#include <QChartView>
#include <QLineSeries>

//#include "cqchartview.h"
//#include "graphicsRoiEllipse.h"
//#include "graphicsRoiCircle.h"
//#include "graphicsRoiPolygon.h"

//#include "graphicsChartItemEllipse.h"
//#include "graphicsChartItemLineSegment.h"
//#include "graphicsChartItemRect.h"
//#include "graphicsChartItemRectOrientation.h"
//#include "graphicsChartItemLineOrientation.h"

#include "graphicsItemPoint.h"

#define QT_MESSAGE_PATTERN "[%{time yyyyMMdd h:mm:ss.zzz} %{if-debug}D%{endif}%{if-info}I%{endif}%{if-warning}W%{endif}%{if-critical}C%{endif}%{if-fatal}F%{endif}] - %{message}"
QT_CHARTS_USE_NAMESPACE
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    qSetMessagePattern(QT_MESSAGE_PATTERN);
    m_view = new GraphicsView(this);      // The view does not take ownership of scene
    QPixmap defaultPixmap(800, 600);
    defaultPixmap.fill(Qt::white);
    m_view->setPixmap(defaultPixmap);
//    CQChartView *chartView = new CQChartView;
    QSplitter *splitter = new QSplitter;
    splitter->addWidget(m_view);
//    splitter->addWidget(chartView);
    splitter->setSizes(QList<int>()<<300<<500);
    this->setCentralWidget(splitter);     // Note: QMainWindow takes ownership of the widget pointer and deletes it at the appropriate time.

    m_rectRoi = new GraphicsRoiRect(QPointF(100,100), QSizeF(111,111), m_view->getGraphicsPixmapItem(), EdgeMove);
//    m_rectRoi->setPenColor(QColor(153, 204, 255).darker());
//    m_rectRoi->setAnchorBordeColor(QColor(153, 204, 255).darker());
//    m_rectRoi->setBrushColor(QColor(153, 204, 255, 200));
//    m_rectRoi->setAnchorFillColor(QColor(153, 204, 255, 200));
//    connect(m_rectRoi, &GraphicsRoiRect::rectChanged, [=](const QRectF& r) {qDebug() << r; });

//    GraphicsRoiEllipse *ellipseRoi = new GraphicsRoiEllipse(QPointF(300,300), QSizeF(111,222), m_view->getGraphicsPixmapItem());
//    ellipseRoi->setPenColor(Qt::red);
//    ellipseRoi->setBrushColor(QColor(153, 204, 255, 200));
//    ellipseRoi->setStartAngle(30*16);
//    ellipseRoi->setSpanAngle(311*16);

//    GraphicsRoiCircle *circleRoi = new GraphicsRoiCircle(QPointF(500,300), 80, m_view->getGraphicsPixmapItem());
//    circleRoi->setPenColor(Qt::red);

    GraphicsItemPixmap *pixmapItem = m_view->getGraphicsPixmapItem();
    GraphicsItemPoint *itemAnchor = new GraphicsItemPoint(QPointF(400, 300), QSizeF(9, 9), GraphicsItemPoint::Circle, pixmapItem, pixmapItem);
    itemAnchor->setFlag(QGraphicsItem::ItemIsMovable, true);

//    GraphicsRoiPolygon *polygonRoi = new GraphicsRoiPolygon(m_view->getGraphicsPixmapItem());

//    GraphicsChartItemEllipse *chartItemEllipse = new GraphicsChartItemEllipse(chartView, chartView->chart());
//    chartItemEllipse->setEllepse(QPointF(0, 0), QSizeF(25,25));
//    chartItemEllipse->setBrushColor(QColor(153, 204, 255, 200));

//    GraphicsChartItemLineSegment *chartItemLine = new GraphicsChartItemLineSegment(chartView, chartView->chart());
//    chartItemLine->setLine(QPointF(-25, -20), QPointF(25, 20));

//    GraphicsChartItemRect *chartItemRect = new GraphicsChartItemRect(chartView, chartView->chart());
//    chartItemRect->setRect(QRectF(QPointF(-24, 1), QPointF(24, 21)));
//    chartItemRect->setBrushColor(QColor(153, 204, 255, 200));

//    GraphicsChartItemRectOrientation *chartItemRectOrientation = new GraphicsChartItemRectOrientation(chartView, chartView->chart());
//    chartItemRectOrientation->setRect(-37.5, 12.5, Qt::Vertical);
//    chartItemRectOrientation->setBrushColor(QColor(153, 204, 255, 200));

//    GraphicsChartItemLineOrientation *chartItemLineOrientation = new GraphicsChartItemLineOrientation(chartView, chartView->chart());
//    chartItemLineOrientation->setLine(-19.5, Qt::Horizontal);

    initWidgets();
}

MainWindow::~MainWindow()
{

}

void MainWindow::initWidgets()
{
    m_actFileOpen = new QAction(QIcon(), tr("&Open"), this);
    connect(m_actFileOpen, &QAction::triggered, [=]()
    {
        if (m_rectRoi)
        {
            delete m_rectRoi;
            m_rectRoi = 0;
        }
    });

    QMenu *m_fileMenu = menuBar()->addMenu(QIcon(), "&File");
    m_fileMenu->addAction(m_actFileOpen);
}
