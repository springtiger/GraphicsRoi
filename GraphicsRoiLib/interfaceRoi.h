#ifndef ITERFACEROI_H
#define ITERFACEROI_H

#include <QColor>
#include <QObject>
#include <QGraphicsItem>

class GraphicsShapeItem;
class GraphicsItemLine;
class IRoi
{
public:
    IRoi(GraphicsShapeItem *roi);
public:
    virtual void setAnchorBordeColor(const QColor& color) = 0;
    virtual void setAnchorFillColor (const QColor& color) = 0;
    virtual void setRotatable(bool set) = 0;
    virtual void setResizable(bool set) = 0;
    virtual void setManipulatable(bool set);
    virtual void setCenterVisible(bool set);
    virtual bool rotatable();
    virtual bool resizable();
    virtual bool manipulatable();
protected:
    void init();
    void updateCenter();
protected:
    GraphicsShapeItem *m_pRoi;
    QColor m_clrAnchorBordeColor;
    QColor m_clrAnchorFillColor ;
    GraphicsItemLine *m_pLineV;
    GraphicsItemLine *m_pLineH;
    bool m_bRotatable;
    bool m_bResizable;
    bool m_bManipulatable;
};

QT_BEGIN_NAMESPACE
#define IRoi_iid "org.qt-project.Qt.GraphicsRoiLib.IRoi"
Q_DECLARE_INTERFACE(IRoi, IRoi_iid)
QT_END_NAMESPACE

#endif // ITERFACEROI_H
