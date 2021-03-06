﻿#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H
#include <QGraphicsView>
#include <QResizeEvent>
#include <QGraphicsScene>
#include <QResizeEvent>
#include <QDebug>
#include <QMarginsF>
#include <QTime>
#include "graphicsItemPixmap.h"

//class QGraphicsSimpleTextItem;
//class GraphicsSimpleTextItem;
class GraphicsLayoutItemSimpleText;

class GraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    GraphicsView(QWidget *parent); // parent 必须设置，以便 QGraphicsScene 释放

    enum PixmapResizePolicyFlag
    {
        Hold         = 0x01,
        MoveToCenter = 0x02,
        OriginalSize = 0x04,
        OptimalSize  = 0x08,
    };
    Q_DECLARE_FLAGS(PixmapResizePolicyFlags, PixmapResizePolicyFlag)

    GraphicsItemPixmap *getGraphicsPixmapItem();
    // 图片
    QPixmap getPixmap() const;
    // 当前缩放百分比
    qreal getCurPixmapScaledPercent();
    // 像素单位
    void setMargin(const QMarginsF margin);
Q_SIGNALS:
    void pixmapScaleChanged(qreal scale);
public slots:
    //
    void setPixmap(const QPixmap& getPixmap);
    // 移动到中心
    void doMovePixmapToViewCenter();
    // 原始尺寸-只调整了缩放比率，没有移动到中心
    void doResetPixmapScale();
    // 自适应缩放-只调整了缩放比率，没有移动到中心
    void doSetToOptimalScale();
    // 缩放倍数区间-min，max倍数
    void setScaleRange(qreal min = 0.1, qreal max = 10);
    // 缩放倍数
    void setScale(qreal scale);
    // 按钮
    void onResetButtonClicked();
    void onAutoSizeButtonClicked();
    // 执行布局
    void doUpdateLayout();
    //
    void doUpdateFPS();
    //
    void setWidgetsLayerOpcityOnLostCapture(qreal opcity = 0);
protected:
    void initView();
    void initScene();
    void initFpsUpdater();
protected:
    virtual void resizeEvent(QResizeEvent *event)   override;
    virtual void wheelEvent(QWheelEvent *event)     override;
    virtual void mousePressEvent(QMouseEvent *event)override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;
    virtual void enterEvent(QEvent *event)          override;
    virtual void leaveEvent(QEvent *event)          override;
private:
    QGraphicsWidget *m_baseWidget;
    GraphicsItemPixmap *m_pixmapItem;
    GraphicsLayoutItemSimpleText *m_simpleTextItem;
    QMarginsF m_margin;
    int m_distExp;
    QTime m_fpsTimer;
    int m_frameCount;
    qreal m_widgetsLayerOpcityOnLostCapture;

    qreal m_scaleRangeMin;
    qreal m_scaleRangeMax;
    PixmapResizePolicyFlags m_pixmapResizePolicy;
};
Q_DECLARE_OPERATORS_FOR_FLAGS(GraphicsView::PixmapResizePolicyFlags)

#endif // GRAPHICSVIEW_H
