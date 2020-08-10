#include "graphicsview.h"

#include <QtMath>
#include <QGraphicsAnchorLayout>
#include <QGraphicsWidget>
#include <QPushButton>
#include <QGraphicsProxyWidget>
#include <QGraphicsLinearLayout>
#include <QTextCursor>
#include <QGraphicsDropShadowEffect>
#include <QCoreApplication>
#include <QGraphicsSimpleTextItem>

#include "graphicsRoiRect.h"
#include "graphicsItemRect.h"

#include "graphicsLayoutItemSimpleText.h"
#include "graphicsItemSimpleText.h"


namespace GraphicsRoi
{

GraphicsView::GraphicsView(QWidget *parent)
    : QGraphicsView(parent)
    , m_distExp(600)
    , m_pixmapItem(0)
    , m_baseWidget(0)
    , m_scaleRangeMin(std::numeric_limits<qreal>::min())
    , m_scaleRangeMax(std::numeric_limits<qreal>::max())
    , m_margin(QMarginsF(1,1,1,1))
    , m_widgetsLayerOpcityOnLostCapture(0.1)
{
    initView();
    initScene();
    initFpsUpdater();
}

GraphicsItemPixmap *GraphicsView::getGraphicsPixmapItem()
{
    return m_pixmapItem;
}

void GraphicsView::initFpsUpdater()
{
    m_fpsTimer.start();
    m_frameCount = 0;
}

void GraphicsView::resizeEvent(QResizeEvent *event)
{
    if (scene())
    {
        scene()->setSceneRect(QRectF(QPoint(0, 0), event->size()));
    }
    QGraphicsView::resizeEvent(event);
}


void GraphicsView::initView()
{
    //setRenderHint(QPainter::Antialiasing);
    //setRenderHint(QPainter::TextAntialiasing);
}

void GraphicsView::initScene()
{
    m_pixmapResizePolicy |= OptimalSize;
    m_pixmapResizePolicy |= MoveToCenter;

    setScene(new QGraphicsScene(this->parent())); // The view does not take ownership of scene
    scene()->setSceneRect(0,0, 100,100); // 如果不设置一个默认大小，当往scene添加元素，将触发sceneRectChanged，然后又将触发doUpdateLayout，可能引起scene大小调整再次触发触发sceneRectChanged，接着就可能死循环。

    QPixmap tile = QPixmap(128, 128);
    tile.fill(Qt::white);
    QPainter pt(&tile);
    QColor color(230, 230, 230);
    pt.fillRect(0, 0, 64, 64, color);
    pt.fillRect(64, 64, 64, 64, color);
    pt.end();

    scene()->setBackgroundBrush(QBrush(tile));
    // 当scene尺寸变化时，适应图片，并将图片移到中心
    connect(scene(), &QGraphicsScene::sceneRectChanged, this, &GraphicsView::doUpdateLayout);

    QPixmap defaultPixmap(800, 600);
    defaultPixmap.fill(Qt::lightGray);
    m_pixmapItem = new GraphicsItemPixmap(defaultPixmap);
    m_pixmapItem->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsFocusable); // 必须设置ItemIsMovable|ItemIsSelectable|ItemIsFocusable,否则鼠标移动图片不正常。原因：GraphicsView::mouseMoveEvent
    connect(scene(), &QGraphicsScene::focusItemChanged, [this](QGraphicsItem *newFocus, QGraphicsItem *, Qt::FocusReason){ if (newFocus == m_pixmapItem)  m_pixmapResizePolicy = Hold; });
    scene()->addItem(m_pixmapItem);
    // 创建阴影效果
    QGraphicsDropShadowEffect *drapShadowEffect = new QGraphicsDropShadowEffect;
    drapShadowEffect->setColor(Qt::black);
    drapShadowEffect->setOffset(0,0);
    drapShadowEffect->setBlurRadius(6);
    //
    m_simpleTextItem = new GraphicsLayoutItemSimpleText(tr("FPS: 0"));
    m_simpleTextItem->setGraphicsEffect(drapShadowEffect);
    m_simpleTextItem->setBrush(Qt::white);
    //m_simpleTextItem->setBackgroundBrush(Qt::red);
    m_simpleTextItem->setOpacity(1);
    m_simpleTextItem->setPos(QPointF(15,26));
    scene()->addItem(m_simpleTextItem);

    // 按钮
    QPushButton *reset = new QPushButton(tr("Reset"));
    connect(reset, &QPushButton::clicked, this, &GraphicsView::onResetButtonClicked);
    QGraphicsProxyWidget *proxyReset = new QGraphicsProxyWidget;
    proxyReset->setWidget(reset);
    // 按钮
    QPushButton *autoSize = new QPushButton(tr("Auto layout"));
    connect(autoSize, &QPushButton::clicked, this, &GraphicsView::onAutoSizeButtonClicked);
    QGraphicsProxyWidget *proxyAutoSize = new QGraphicsProxyWidget;
    proxyAutoSize->setWidget(autoSize);

    // 按钮布局
    QGraphicsLinearLayout *lineLayout = new QGraphicsLinearLayout;
    lineLayout->setOrientation(Qt::Vertical);
    lineLayout->setContentsMargins(0,10,0,0);
    lineLayout->addItem(proxyAutoSize);
    lineLayout->addItem(proxyReset);

    // 总布局
    QGraphicsAnchorLayout *baseLayout = new QGraphicsAnchorLayout;
    baseLayout->addAnchor(baseLayout, Qt::AnchorTop,   lineLayout, Qt::AnchorTop);
    baseLayout->addAnchor(baseLayout, Qt::AnchorRight, lineLayout, Qt::AnchorRight);

    m_baseWidget = new QGraphicsWidget;
    m_baseWidget->setOpacity(m_widgetsLayerOpcityOnLostCapture);
    m_baseWidget->setLayout(baseLayout);
    connect(scene(), &QGraphicsScene::sceneRectChanged, [this](const QRectF& r){ m_baseWidget->setGeometry(r);});

    // 添加
    scene()->addItem(m_baseWidget);
}


void GraphicsView::setPixmap(const QPixmap& pixmap, const QString& pixmapPath)
{
    doUpdateFPS();

    m_pixmapPath = pixmapPath;
    if (m_pixmapItem == 0) return;
    bool trigger = this->getPixmap().isNull() || this->getPixmap().size() != pixmap.size();

    m_pixmapItem->setPixmap(pixmap);

    //
    if (trigger)
    {
        doUpdateLayout();
    }
}


QPixmap GraphicsView::getPixmap() const
{
    if (m_pixmapItem)
        return m_pixmapItem->pixmap();
    return QPixmap();
}

QString GraphicsView::getPixmapPath() const
{
    return m_pixmapPath;
}

void GraphicsView::doMovePixmapToViewCenter()
{
    if (m_pixmapItem == 0) return;
    // 移动到中心
    QRectF rect = m_pixmapItem->boundingRect();
    rect = m_pixmapItem->mapToScene(rect).boundingRect();

    QPointF newPos = rect.topLeft() + ( this->scene()->sceneRect().center() - rect.center());

    rect.moveCenter(this->scene()->sceneRect().center());

    m_pixmapItem->setPos(newPos);
}

void GraphicsView::doResetPixmapScale()
{
    if (m_pixmapItem == 0) return;

    setScale(0.9999); // 假如直接设置为1,ROI显示异常（有残影），怀疑是Qt的bug
}

void GraphicsView::doSetToOptimalScale()
{
    if (m_pixmapItem == 0 || m_pixmapItem->pixmap().isNull()) return;

    QRectF pixmapRect = m_pixmapItem->boundingRect();
    QRectF maginedSceneRect = scene()->sceneRect().marginsRemoved(m_margin);
    // 从宽度、高度比例中，取较小的值为缩放系数
    qreal minScale = qMax(pixmapRect.width()/maginedSceneRect.width(),
                          pixmapRect.height()/maginedSceneRect.height());

    setScale(1/minScale);
}

qreal GraphicsView::getCurPixmapScaledPercent()
{
    if (m_pixmapItem == 0) return 100;

    return m_pixmapItem->scale() * 100;
}

void GraphicsView::setScale(qreal scale)
{
    if (m_pixmapItem == 0) return;

    if (scale < m_scaleRangeMin)
        scale = m_scaleRangeMin;
    else if (scale > m_scaleRangeMax)
        scale = m_scaleRangeMax;

    m_pixmapItem->setScale(scale);

    // 更新 m_distExp 值
    m_distExp  = logf(m_pixmapItem->scale()*1.5)/logf((float)M_E) * 1200;

    emit pixmapScaleChanged(m_pixmapItem->scale());
}

void GraphicsView::onResetButtonClicked()
{
    m_pixmapResizePolicy |= OriginalSize;
    m_pixmapResizePolicy &= ~OptimalSize;
    m_pixmapResizePolicy |= MoveToCenter;

    doUpdateLayout();
}

void GraphicsView::onAutoSizeButtonClicked()
{
    m_pixmapResizePolicy &= ~OriginalSize;
    m_pixmapResizePolicy |= OptimalSize;
    m_pixmapResizePolicy |= MoveToCenter;
    doUpdateLayout();
}

void GraphicsView::doUpdateLayout()
{
    //qDebug() <<<< "doUpdateLayout" << this->sceneRect();
    if (m_pixmapResizePolicy & OriginalSize)
    {
        doResetPixmapScale();
    }
    else if (m_pixmapResizePolicy & OptimalSize)
    {
        doSetToOptimalScale();
    }

    if (m_pixmapResizePolicy & MoveToCenter)
    {
        doMovePixmapToViewCenter();
    }
}

void GraphicsView::doUpdateFPS()
{
    //qDebug() <<<< "doUpdateFPS";
    m_frameCount++;
    int elapsed = m_fpsTimer.elapsed();
    if (elapsed >= 1000) {
        elapsed = m_fpsTimer.restart();
        qreal fps = qreal(0.1 * int(10000.0 * (qreal(m_frameCount) / qreal(elapsed))));
        m_simpleTextItem->setText(tr("FPS: %1").arg(QString::number(fps, 'f', 1)));
        m_frameCount = 0;
    }
}

void GraphicsView::setWidgetsLayerOpcityOnLostCapture(qreal opcity)
{
    m_widgetsLayerOpcityOnLostCapture = opcity;
}

void GraphicsView::clearOverlays()
{
    foreach (GraphicsShapeItem* item, m_overlays) {
        delete item;
    }
    m_overlays.clear();
}

void GraphicsView::clearAll()
{
    clearOverlays();

    QPixmap defaultPixmap(800, 600);
    defaultPixmap.fill(Qt::lightGray);
    setPixmap(defaultPixmap, "");
}

int GraphicsView::removeFromOverlays(GraphicsShapeItem *item)
{
    if (item == 0)
        return 0;
    int n = m_overlays.removeAll(item);
    delete item;
    return n;
}

QList<GraphicsShapeItem *> GraphicsView::overlays()
{
    return m_overlays;
}

const QList<GraphicsShapeItem *> GraphicsView::overlays() const
{
    return m_overlays;
}

QList<GraphicsRoiRect *> GraphicsView::addRects(const QList<QRectF> rects, const QColor &brushColor, const QColor &penColor, bool resizable, bool movable, bool rotatable, AnchorMoveMode mode)
{
    QList<GraphicsRoiRect *> rois;
    foreach (auto rect, rects) {
        rois.append(addRectRoi(rect, brushColor, penColor, resizable, movable, rotatable, mode));
    }
    return rois;
}

GraphicsRoiRect * GraphicsView::addRectRoi(const QRectF &rect, const QColor &brushColor, const QColor &penColor, bool resizable, bool movable, bool rotatable, AnchorMoveMode mode)
{
    GraphicsRoiRect *rectRoi = new GraphicsRoiRect(rect, m_pixmapItem, mode);
    rectRoi->setBrushColor(brushColor);
    rectRoi->setPenColor(penColor);
    rectRoi->setResizable(resizable);
    rectRoi->setRotatable(rotatable);
    rectRoi->setAnchorAutoHide(true);
    rectRoi->setFlag(QGraphicsItem::ItemIsMovable, movable);
    m_overlays.append(rectRoi);
    return rectRoi;
}

GraphicsRoiRect* GraphicsView::findRect(const QRect &rect)
{
    foreach (auto var, m_overlays)
    {
        if (var->type() == GraphicsRoiRect::Type)
        {
            GraphicsRoiRect* rectRoi = qgraphicsitem_cast<GraphicsRoiRect*>(var);
            if (rectRoi->rect().toRect() == rect)
                return rectRoi;
        }
    }
    return 0;
}

GraphicsItemPoint *GraphicsView::addPoint(const QPointF &pos, const QSizeF &size, const QColor &brushColor, const QColor &penColor)
{
    GraphicsItemPoint * itemAnchor= new GraphicsItemPoint(pos, size, GraphicsItemPoint::Circle, m_pixmapItem);
    itemAnchor->setBrushColor(brushColor);
    itemAnchor->setPenColor(penColor);
    m_overlays.append(itemAnchor);
    return itemAnchor;
}

GraphicsItemLine *GraphicsView::addLine(const QLineF &line, const QColor &brushColor, const QColor &penColor)
{
    GraphicsItemLine * item= new GraphicsItemLine(line, m_pixmapItem);
    item->setBrushColor(brushColor);
    item->setPenColor(penColor);
    m_overlays.append(item);
    return item;
}

void GraphicsView::setSingleSelect(GraphicsShapeItem *item)
{
    foreach (auto var, m_overlays) {
        var->setSelected(false);
    }
    if (item)
        item->setSelected(true);
}


void GraphicsView::setScaleRange(qreal min, qreal max)
{
    //qDebug() <<<< "setScaleRange";
    m_scaleRangeMin = qMin(min, max);
    m_scaleRangeMax = qMax(min, max);
    // 重新设置，将引起Min/Max检查
    setScale(m_pixmapItem->scale());
}

void GraphicsView::setMargin(const QMarginsF margin)
{
    m_margin = margin;
}

void GraphicsView::wheelEvent(QWheelEvent *event)
{
    m_distExp += event->delta();
    qreal scale = qPow(M_E, m_distExp / 1200.0f)  / 1.5;
    if (scale < m_scaleRangeMin)
    {
        scale = m_scaleRangeMin;
        m_distExp -= event->delta();
    }
    else if (scale > m_scaleRangeMax)
    {
        scale = m_scaleRangeMax;
        m_distExp -= event->delta();
    }

    GraphicsView *view = this;
    // 鼠标在 QGraphicsView 坐标系中的位置
    QPoint posInView = event->pos();

    // 鼠标在 QGraphicsScene 坐标系中的位置
    QPointF posInScene = view->mapToScene(posInView);

    // 鼠标在 QGraphicsPixmapItem 坐标系中的位置
    QPointF posInPixmap = m_pixmapItem->mapFromScene(posInScene);

    // scale QGraphicsPixmapItem
    m_pixmapItem->setScale(scale);
    emit pixmapScaleChanged(m_pixmapItem->scale());

    // 缩放后，鼠标下的对应的QGraphicsPixmapItem坐标已变化，求缩放前QGraphicsPixmapItem坐标系的那个位置移动到了哪里
    QPointF newPosInScene = m_pixmapItem->mapToScene(posInPixmap);
    // 偏移的距离
    QPointF offset = posInScene - newPosInScene;
    // 根据偏移距离设置图片位置
    m_pixmapItem->setPos(m_pixmapItem->pos() + offset);

    QGraphicsView::wheelEvent(event);
}

QPoint m_lastPos;
void GraphicsView::mousePressEvent(QMouseEvent *event)
{
    m_lastPos = event->pos();
    QGraphicsView::mousePressEvent(event);
}

void GraphicsView::mouseMoveEvent(QMouseEvent *event)
{
    QPoint offset = m_lastPos - event->pos();
    m_lastPos = event->pos();
    if (event->buttons() & Qt::LeftButton && m_pixmapItem && scene()->focusItem() == 0)
    {
        if (m_pixmapResizePolicy != Hold)
            m_pixmapResizePolicy = Hold;
        m_pixmapItem->setPos(m_pixmapItem->pos() - offset);
        return;
    }

    QGraphicsView::mouseMoveEvent(event);
}

void GraphicsView::enterEvent(QEvent *event)
{
    // 进入View时，显示baseWidget,即可操作各种按钮
    if (m_baseWidget)
        m_baseWidget->setOpacity(1);
    QGraphicsView::enterEvent(event);
}

void GraphicsView::leaveEvent(QEvent *event)
{
    if (m_baseWidget)
        m_baseWidget->setOpacity(m_widgetsLayerOpcityOnLostCapture);
    QGraphicsView::leaveEvent(event);
}

}
