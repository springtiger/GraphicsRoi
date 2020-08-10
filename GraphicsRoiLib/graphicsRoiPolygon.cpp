#include "graphicsRoiPolygon.h"
#include <QEvent>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QGraphicsScene>

GraphicsRoiPolygon::GraphicsRoiPolygon(QGraphicsObject *parent)
    : GraphicsItemPolygon(parent)
    , IRoi(this)
{
    init();
}

GraphicsRoiPolygon::GraphicsRoiPolygon(const QPolygonF &polygon, QGraphicsObject *parent)
    : GraphicsItemPolygon(polygon, parent)
    , IRoi(this)
{
    init();
    setPolygon(polygon);
}

void GraphicsRoiPolygon::setPolygon(const QPolygonF &polygon)
{

    GraphicsItemPolygon::setPolygon(polygon);
}

void GraphicsRoiPolygon::append(const QPointF &p)
{
    if(polygon().size() != 1 && polygon().isClosed()) // 已封闭的轮廓不可再添加。一个点时，必然是Closed所以必须去掉这种情况
        return;

    if(polygon().size() > 0 && polygon().last() == p) // 忽略重复点
        return;

    // 先将数据添加到QPolygonF
    GraphicsItemPolygon::append(p);
    // 完成Line,设置P2
    if (m_lineItems.size() > 0)
        m_lineItems.last()->setP2(p);

    if (polygon().size() == 1 || !polygon().isClosed()) // 第一个点必然添加；polygon不封闭才添加Line
    {
        // 添加Line
        m_lineItems.append(new GraphicsPolyLine(this)); // 添加Line时，设置P1
        // 注册事件处理
        m_lineItems.last()->installSceneEventFilter(this);
        // 设置Line点
        m_lineItems.last()->setP1(p);
        m_lineItems.last()->setP2(p);
        // 添加Anchor
        m_anchors.append(new GraphicsAnchor(this, m_anchors.size()));
        m_anchors.last()->setPenColor(m_anchors.size() == 1 ? m_firstAnchorBordeColor : m_colorAnchorBorde);
        m_anchors.last()->setBrushColor(m_anchors.size() == 1 ? m_firstAnchorFillColor : m_colorAnchorFill);
    }

    if (polygon().isClosed() && polygon().size() != 1)
        emit polygonClosed();
    // 设置变换原点
    setTransformOriginPoint(this->boundingRect().center());
}

void GraphicsRoiPolygon::insert(int i, const QPointF &p)
{
    if (!polygon().isClosed()) // 没有封闭的polygon不可以insert
        return;

    qDebug() << "GraphicsPolygonItem::insert";
    // 在封闭轮廓的末尾追加
    if (i < 0 || i >= polygon().size())
    {
        qDebug() << "GraphicsPolygonItem::insert out of range" << i << polygon().size();
        return;
    }

    // 先将数据添加到QPolygonF
    GraphicsItemPolygon::insert(i+1, p);
    // 修改前一条Line的P2
    QPointF p2 = m_lineItems[i]->line().p2();
    m_lineItems[i]->setP2(p);
    // 添加Line
    m_lineItems.insert(i+1, new GraphicsPolyLine(QLineF(p, p2), this));
    // 注册事件处理
    m_lineItems[i+1]->installSceneEventFilter(this);

    // 添加Anchor
    m_anchors.insert(i+1, new GraphicsAnchor(this, i+1));
    m_anchors[i+1]->setPenColor(m_colorAnchorBorde);
    m_anchors[i+1]->setBrushColor (m_colorAnchorFill  );
    // 使Anchor调整编号
    for (int j = i+2; j < m_anchors.size(); j++)
    {
        m_anchors[j]->setPolyIndex(j);
    }
    // 设置变换原点
    setTransformOriginPoint(this->boundingRect().center());
}

void GraphicsRoiPolygon::updatePos(int i, const QPointF &p)
{
    // qDebug() << "GraphicsPolygonRoi::updatePos";
    if (!polygon().isClosed()) // 没有封闭的polygon不可以更新位置
        return;
    //
    GraphicsItemPolygon::updatePos(i, p);
    if (i == 0)
        GraphicsItemPolygon::updatePos(polygon().size()-1, p);

    // 更新Line位置
    m_lineItems[(i-1+m_lineItems.size())%m_lineItems.size()]->setP2(p);
    m_lineItems[i]->setP1(p);
    // Anchor自身会更新位置,再次无需设置
    // 设置变换原点
    setTransformOriginPoint(this->boundingRect().center());
}

void GraphicsRoiPolygon::remove(int i)
{
    if (!polygon().isClosed()) // 没有封闭的polygon不可以
        return;

    if (polygon().size() <= 4) // 最少4个点,否则不允许删除
        return;

    if (i < 0 || i >= polygon().size()) // 索引超出范围
        return;

    if (i == 0 || i == polygon().size()-1)
    {
        GraphicsItemPolygon::remove(0);
        GraphicsItemPolygon::remove(polygon().size()-1);
        GraphicsItemPolygon::append(polygon().first());
    }
    else
    {
        GraphicsItemPolygon::remove(i);
    }

    delete m_anchors[i];
    m_anchors.remove(i);
    for (int j = i; j < m_anchors.size(); j++)
    {
        m_anchors[j]->setPolyIndex(j);
    }

    m_lineItems[(i-1+m_lineItems.size())%m_lineItems.size()]->setP2(m_lineItems[i]->line().p2());
    delete m_lineItems[i];
    m_lineItems.remove(i);
}

void GraphicsRoiPolygon::setAnchorBordeColor(const QColor &color)
{
    m_colorAnchorBorde = color;
    foreach (GraphicsAnchor* anchor, m_anchors) {
        anchor->setPenColor(!polygon().isClosed() && anchor->polyIndex() ==0 ? m_firstAnchorBordeColor : color);
    }
}

void GraphicsRoiPolygon::setAnchorFillColor(const QColor &color)
{
    m_colorAnchorFill = color;
    foreach (GraphicsAnchor* anchor, m_anchors) {
        anchor->setBrushColor(!polygon().isClosed() && anchor->polyIndex() ==0 ? m_firstAnchorFillColor : color);
    }
}

void GraphicsRoiPolygon::setRotatable(bool set)
{
    m_bRotatable = set;

}

void GraphicsRoiPolygon::setResizable(bool set)
{
    if (set == false && !polygon().isClosed())
        return;

    m_bRotatable = set;
    foreach (GraphicsAnchor* anchor, m_anchors) {
        anchor->setVisible(set);
    }
}

void GraphicsRoiPolygon::setFirstAnchorBordeColor(const QColor &color)
{
    m_firstAnchorBordeColor = color;
    if (!polygon().isClosed() && m_anchors.size() > 0)
    {
        m_anchors.first()->setPenColor(color);
    }
}

void GraphicsRoiPolygon::setFirstAnchorFillColor(const QColor &color)
{
    m_firstAnchorFillColor = color;
    if (!polygon().isClosed() && m_anchors.size() > 0)
    {
        m_anchors.first()->setBrushColor(color);
    }
}

int GraphicsRoiPolygon::type() const
{
    return Type;
}

void GraphicsRoiPolygon::anchorPressed()
{
    if (polygon().isClosed())
        return;

    GraphicsAnchor* anchor = qobject_cast<GraphicsAnchor*>(sender());
    if (polygon().size() > 1 && anchor->polyIndex() == 0)
    {// 使封闭
        append(polygon().first());
    }
}

void GraphicsRoiPolygon::anchorDoubleClicked()
{
    // 删除
}

void GraphicsRoiPolygon::init()
{
    this->setFlag(ItemIsMovable);
    this->setFlag(ItemIsSelectable);
    this->setFlag(ItemIsFocusable);
    this->setCosmetic(true);
    this->setFiltersChildEvents(true);
    this->setPenColor(Qt::transparent);
    this->setBrushColor(QColor(153, 204, 255, 200));

    m_colorAnchorBorde = QColor(Qt::black);
    m_colorAnchorFill  = QColor(153, 204, 255, 200);
    m_firstAnchorBordeColor   = QColor(Qt::black);
    m_firstAnchorFillColor    = QColor(255, 204, 255, 200);
    //
    setAcceptHoverEvents(true);
    // 注册事件处理，点击图片时，添加节点。
    parentObject()->installSceneEventFilter(this);
    // hover
    static bool acceptHover = parentObject()->acceptHoverEvents();
    parentObject()->setAcceptHoverEvents(true);
    parentObject()->setFiltersChildEvents(true);
    // 多边形已封闭时，移除事件处理，不可再添加
    connect(this, &GraphicsRoiPolygon::polygonClosed, this, [this]()
    {
        qDebug() << "polygon closed.";
        setAcceptHoverEvents(false);
        parentObject()->removeSceneEventFilter(this);
        parentObject()->setAcceptHoverEvents(acceptHover);
        parentObject()->setFiltersChildEvents(false);
        m_anchors.first()->setPenColor(m_colorAnchorBorde);
        m_anchors.first()->setBrushColor(m_colorAnchorFill);
    });

    connect(parentObject(), &QGraphicsObject::scaleChanged, this, [=](){
        QList<QGraphicsItem*> items = this->childItems();
        foreach (QGraphicsItem *item, items) {
            GraphicsShapeItem *shapeItem = qgraphicsitem_cast<GraphicsShapeItem *>(item);
            if (shapeItem)
                shapeItem->updateShape();
        }
    });
}

bool GraphicsRoiPolygon::sceneEventFilter(QGraphicsItem *watched, QEvent *event)
{
    if (event->type() == QEvent::GraphicsSceneMousePress)
    {
        QGraphicsSceneMouseEvent *sceneEvent = static_cast<QGraphicsSceneMouseEvent *>(event);
        if (polygon().size() > 1 && polygon().isClosed())
        { // 插入
            if (watched->type() == GraphicsPolyLine::Type)
            {
                GraphicsPolyLine* line = qgraphicsitem_cast<GraphicsPolyLine*>(watched);
                int index = m_lineItems.indexOf(line);
                this->insert(index, watched->mapToItem(this, sceneEvent->pos()));
                return true;
            }
        }
        else
        { // 添加
            QGraphicsSceneMouseEvent *sceneEvent = static_cast<QGraphicsSceneMouseEvent *>(event);
            if (polygon().size() > 1 && !polygon().isClosed() && m_anchors.first()->boundingRect().contains(watched->mapToItem(m_anchors.first(), sceneEvent->pos())))
            {
                append(polygon().first());
            }
            else
            {
                append(watched->mapToItem(this, sceneEvent->pos()));
            }
            return true;
        }
    }
    else if (event->type() == QEvent::GraphicsSceneMouseDoubleClick)
    {
        if (polygon().size() > 1 && polygon().isClosed())
        {
            GraphicsAnchor* anchor = qgraphicsitem_cast<GraphicsAnchor*>(watched);
            if (m_anchors.contains(anchor))
            {
                this->remove(anchor->polyIndex());
                return true;
            }
        }
    }
    else if (event->type() == QEvent::GraphicsSceneHoverMove)
    {
        QGraphicsSceneMouseEvent *sceneEvent = static_cast<QGraphicsSceneMouseEvent *>(event);
        if (m_lineItems.size() > 0 && polygon().size() > 0 && (!polygon().isClosed() || polygon().size() == 1))
            m_lineItems.last()->setP2(watched->mapToItem(this, sceneEvent->pos()));
    }

    return GraphicsItemPolygon::sceneEventFilter(watched, event);
}

void GraphicsRoiPolygon::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    GraphicsItemPolygon::paint(painter, option, widget);

    if (m_anchors.count() > 2)
        paintCenter(painter, option, widget);
}

void GraphicsRoiPolygon::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    return GraphicsItemPolygon::mouseMoveEvent(event);
}

void GraphicsRoiPolygon::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    //qDebug() << "GraphicsPolygonRoi::hoverEnterEvent";
    return GraphicsItemPolygon::hoverEnterEvent(event);
}

void GraphicsRoiPolygon::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    //qDebug() << "GraphicsPolygonRoi::hoverLeaveEvent";
    return GraphicsItemPolygon::hoverLeaveEvent(event);
}

void GraphicsRoiPolygon::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
//    qDebug() << "GraphicsPolygonRoi::hoverMoveEvent";
//    if (polygon().size() > 1 && !polygon().isClosed())
//        m_lineItems.last()->setP2(event->pos());
    return GraphicsItemPolygon::hoverMoveEvent(event);
}
