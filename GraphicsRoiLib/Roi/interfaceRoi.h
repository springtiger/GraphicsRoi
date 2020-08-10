#ifndef ITERFACEROI_H
#define ITERFACEROI_H

#include <QColor>
#include <QObject>
#include <QGraphicsItem>

#include "graphicsItemPoint.h"

using namespace GraphicsShapes;
//class GraphicsShapeItem;
//class GraphicsItemLine;

class IRoi
{
public:
    IRoi(GraphicsShapeItem *roi);
public:
    virtual void setAnchorBordeColor(const QColor& color) = 0;
    virtual void setAnchorFillColor (const QColor& color) = 0;
    virtual void setResizeAnchorVisible(bool set) = 0;
    virtual void setRotateAnchorVisible(bool set) = 0;
    virtual void setRotatable(bool set) = 0;
    virtual void setResizable(bool set) = 0;
    virtual void setMovable(bool set) = 0;
    virtual void setCentreVisible(bool set) = 0;
    virtual void setAnchorAutoHide(bool set) = 0;

    bool centreVisible();
    bool rotatable();
    bool resizable();
protected:
    QColor m_colorAnchorBorde;// 调节点颜色
    QColor m_colorAnchorFill ;// 调节点颜色

    bool m_bRotatable;  // 可旋转的
    bool m_bResizable;  // 可调整尺寸的
    bool m_bCentreVisible;
    bool m_bAnchorAutoHide;
};

QT_BEGIN_NAMESPACE
#define IRoi_iid "org.qt-project.Qt.GraphicsRoiLib.IRoi"
Q_DECLARE_INTERFACE(IRoi, IRoi_iid)
QT_END_NAMESPACE

#endif // ITERFACEROI_H
