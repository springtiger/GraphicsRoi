#ifndef GRAPHICSANCHOR_H
#define GRAPHICSANCHOR_H

#include "graphicsroilib_global.h"
#include "graphicsItemPoint.h"



class GraphicsAnchorPrivate;
class GRAPHICSROILIBSHARED_EXPORT GraphicsAnchor : public GraphicsItemPoint
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
public:

    // Anchor位置：
    enum AnchorPositionFlag
    {
        BordeLeft        = 0x1   , // 边界框
        BordeRight       = 0x2   , // 边界框
        BordeTop         = 0x4   , // 边界框
        BordeBottom      = 0x8   , // 边界框
        BordeEdges       = BordeLeft|BordeRight|BordeTop|BordeBottom,
        BordeTopLeft     = 0x10  ,
        BordeTopRight    = 0x20  ,
        BordeBottomLeft  = 0x40  ,
        BordeBottomRight = 0x80  ,
        BordeCorners     = BordeTopLeft|BordeTopRight|BordeBottomLeft|BordeBottomRight,
        BordePositions   = BordeEdges|BordeCorners,

        InnerLeft        = 0x100 , // 内边界框
        InnerRight       = 0x200 , // 内边界框
        InnerTop         = 0x400 , // 内边界框
        InnerBottom      = 0x800 , // 内边界框
        InnerPositions   = InnerLeft|InnerRight|InnerTop|InnerBottom,

        OuterLeft        = 0x1000, // 边界框外部
        OuterRight       = 0x2000, // 边界框外部
        OuterTop         = 0x4000, // 边界框外部
        OuterBottom      = 0x8000, // 边界框外部
        OuterPositions   = OuterLeft|OuterRight|OuterTop|OuterBottom,

        ByAngleStart     = 0x10000,
        ByAngleSpan      = 0x20000,
        Center           = 0x40000, // 中心
        PolyPos          = 0x80000, // Polygong
    };
    Q_DECLARE_FLAGS(AnchorPositionFlags, AnchorPositionFlag)
    // Anchor移动模式：不可移动/一条边移动/对边移动/四边移动/旋转/Polygon点移动
    enum ActionMode
    {
        EdgeMove      = 0x1,  // 一条边移动
        OppositeMove  = 0x2,  // 对边同时移动
        WholeMove     = 0x4,  // 四边同时移动
        Rotation      = 0x8,  // 旋转
        PolyPointMove = 0x10,
        AngleSpan     = 0x20,
    };
    Q_ENUM(ActionMode)


    // 构造函数
protected:
    GraphicsAnchor(GraphicsAnchorPrivate &dd, QGraphicsObject *parent);
public:
    GraphicsAnchor(GraphicsShapeItem *parent);
    // For RectRoi\EllipseRoi\CirclrRoi的构造函数
    GraphicsAnchor(GraphicsShapeItem *parent, AnchorPositionFlag pos, ActionMode actionMode = EdgeMove, ShapeStyle shapeStyle = Rectangle, const QSizeF& size = QSizeF(9,9));
    // For Polygon的构造函数
    GraphicsAnchor(GraphicsShapeItem *parent, int polyIndex, ShapeStyle shapeStyle = Rectangle, const QSizeF& size = QSizeF(9,9));

    ~GraphicsAnchor();
public:
    enum { Type = UserType + UserType + 0 };
    virtual int type() const Q_DECL_OVERRIDE;

    void setAntialiasing(bool antialiasing);
    int polyIndex();
    void setPolyIndex(int index);

// 公开 overrde
public:

signals:
    void anchorSwapTrigered(AnchorPositionFlag from, AnchorPositionFlag to);
    void mousePressed();
    void mouseDoubleClicked();
public slots:
    void updateAnchorPos();
protected:
    void init();
protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR) override;
private:
    Q_DISABLE_COPY(GraphicsAnchor)
    Q_DECLARE_PRIVATE_D(QGraphicsItem::d_ptr.data(), GraphicsAnchor)
};
Q_DECLARE_OPERATORS_FOR_FLAGS(GraphicsAnchor::AnchorPositionFlags)

#endif // GRAPHICSANCHOR_H
