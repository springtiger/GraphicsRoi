#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "view/graphicsview.h"
#include "roi/graphicsRoiRect.h"

using namespace GraphicsRoi;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void initWidgets();
private:
    GraphicsView *m_view;

    QAction *m_actFileOpen;
    GraphicsRoiRect *m_rectRoi;
};

#endif // MAINWINDOW_H
