#include "graphicsPolyLine.h"
#include "graphicsPolyLine_p.h"
#include <QCursor>
#include <QBitmap>
#include <QStyleOptionGraphicsItem>
#include <QPainter>
#include <QWidget>
#include <QPainterPath>
#include "graphicsShapeItem.h"

// 定义鼠标检测宽度为15像素
#define MouseDetectWidth 15


void GraphicsPolyLinePrivate::updateShapePath() const
{
    Q_Q(const GraphicsPolyLine);
    QPainterPath path;
    if (m_line == QLineF()) {
        m_shapePath = path;
        return;
    }

    path.moveTo(m_line.p1());
    path.lineTo(m_line.p2());

    // 屏幕的像素转换, 使之不受缩放系数影响
    QPointF p0 = q->mapFromScene(QPointF(0, 0));
    QPointF p1 = q->mapFromScene(QPointF(0, MouseDetectWidth));
    qreal length = QLineF(p0, p1).length();
    // 设置鼠标检测宽度
    QPen pen = m_pen;
    pen.setWidthF(length);

    m_shapePath = GraphicsShapeItem::qt_graphicsItem_shapeFromPath(path, pen);
}

GraphicsPolyLine::GraphicsPolyLine(QGraphicsObject *parent)
    : GraphicsItemLine(*new GraphicsPolyLinePrivate, parent)
{
    init();
}

GraphicsPolyLine::GraphicsPolyLine(const QLineF &line, QGraphicsObject *parent)
    : GraphicsItemLine(*new GraphicsPolyLinePrivate, parent)
{
    init();
    setLine(line);
}

GraphicsPolyLine::GraphicsPolyLine(qreal x1, qreal y1, qreal x2, qreal y2, QGraphicsObject *parent)
    : GraphicsItemLine(x1, y1, x2, y2, parent)
{
    init();
    setLine(QLineF(QPointF(x1, y1), QPointF(x2, y2)));
}

void GraphicsPolyLine::setP1(const QPointF &p)
{
    GraphicsItemLine::setP1(p);
    updateCursor();
}

void GraphicsPolyLine::setP2(const QPointF &p)
{
    GraphicsItemLine::setP2(p);
    updateCursor();
}

void GraphicsPolyLine::setLine(const QLineF &line)
{
    GraphicsItemLine::setLine(line);
    updateCursor();
}


void GraphicsPolyLine::init()
{
    this->setCosmetic(true); // 线宽始终为1像素

    updateCursor();
}

void GraphicsPolyLine::updateCursor()
{
    if (this->line().isNull())
    {
        setCursor(parentObject()->cursor());
    }
    else
    {
        //qreal angle = this->line().angle();
        QCursor cur(Qt::UpArrowCursor);
        setCursor(cur);
//        QImage img = cur.bitmap()->toImage();
//        img.save("C:\\Users\\rd\\Desktop\\cursor.bmp");
    }
}

void GraphicsPolyLine::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setRenderHint(QPainter::Antialiasing);
    GraphicsItemLine::paint(painter, option, widget);
}


