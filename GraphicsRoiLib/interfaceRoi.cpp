#include "interfaceRoi.h"
#include "graphicsShapeItem.h"
#include "graphicsItemLine.h"
#include <QObject>
#include <QDebug>
#include <QGraphicsScene>
#include <graphicsRoiPolygon.h>

#define LENGTH 9

IRoi::IRoi(GraphicsShapeItem *roi)
    : m_clrAnchorBordeColor(QColor(153, 204, 255, 200).dark())
    , m_clrAnchorFillColor (QColor(153, 204, 255, 200))
    , m_pRoi(roi)
{
    Q_ASSERT(m_pRoi);

    init();
}

void IRoi::init()
{
    m_pLineV = new GraphicsItemLine(m_pRoi);
    m_pLineH = new GraphicsItemLine(m_pRoi);
    m_pLineV->setCosmetic(true);
    m_pLineH->setCosmetic(true);

    m_pRoi->connect(m_pRoi->parentObject(), &QGraphicsObject::scaleChanged, m_pRoi, [=](){
        updateCenter();
    });
    m_pRoi->connect(m_pRoi, &GraphicsShapeItem::shapeChanged, m_pRoi, [=](){
        updateCenter();
    });
}

void IRoi::updateCenter()
{
    if (m_pRoi->type() == GraphicsRoiPolygon::Type)
    {
        return;
    }
    // 屏幕的9像素转换到roi的值
    QPointF p0 = m_pRoi->mapFromScene(QPointF(0, 0));
    QPointF p1 = m_pRoi->mapFromScene(QPointF(0, 9));
    qreal halfLength = QLineF(p0, p1).length() / 2;
    // 设置
    QPointF center = m_pRoi->boundingRect().center();

    m_pLineV->setLine(QLineF(QPointF(center.x(), center.y()-halfLength), QPointF(center.x(), center.y()+halfLength)));
    m_pLineH->setLine(QLineF(QPointF(center.x()-halfLength, center.y()), QPointF(center.x()+halfLength, center.y())));
}


void IRoi::setCenterVisible(bool set)
{
    m_pLineV->setVisible(set);
    m_pLineH->setVisible(set);
}

bool IRoi::rotatable()
{
    return m_bRotatable;
}

bool IRoi::resizable()
{
   return m_bResizable;
}

bool IRoi::manipulatable()
{
    return m_bRotatable && m_bResizable;
}


void IRoi::setManipulatable(bool set)
{
    setRotatable(set);
    setResizable(set);
}

