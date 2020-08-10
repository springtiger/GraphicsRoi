#include "graphicsItemSimpleText.h"
#include "graphicsItemSimpleText_p.h"
#include <QTextLayout>
#include <private\qtextengine_p.h>
#include "graphicsShapeItem_p.h"

namespace GraphicsShapes
{

static QRectF setupTextLayout(QTextLayout *layout)
{
    layout->setCacheEnabled(true);
    layout->beginLayout();
    while (layout->createLine().isValid())
    ;
    layout->endLayout();
    qreal maxWidth = 0;
    qreal y = 0;
    for (int i = 0; i < layout->lineCount(); ++i) {
        QTextLine line = layout->lineAt(i);
        maxWidth = qMax(maxWidth, line.naturalTextWidth());
        line.setPosition(QPointF(0, y));
        y += line.height();
    }
    return QRectF(0, 0, maxWidth, y);
}

void GraphicsItemSimpleTextPrivate::updateShapePath() const
{
    QRectF br;
    if (text.isEmpty()) {
        br = QRectF();
    } else {
        QString tmp = text;
        tmp.replace(QLatin1Char('\n'), QChar::LineSeparator);
        QStackTextEngine engine(tmp, font);
        QTextLayout layout;
        QTextEngine *eng = layout.engine();
        *eng = engine;
        br = setupTextLayout(&layout);
    }

    QPainterPath path;
    path.addRect(br);
    m_shapePath = path;

    m_boundingRect = br;
}

/*!
    \class GraphicsSimpleTextItem
    \brief The GraphicsSimpleTextItem class provides a simple text path item
    that you can add to a QGraphicsScene.
    \since 4.2
    \ingroup graphicsview-api
    \inmodule QtWidgets

    To set the item's text, you can either pass a QString to
    GraphicsSimpleTextItem's constructor, or call setText() to change the
    text later. To set the text fill color, call setBrush().

    The simple text item can have both a fill and an outline; setBrush() will
    set the text fill (i.e., text color), and setPen() sets the pen that will
    be used to draw the text outline. (The latter can be slow, especially for
    complex pens, and items with long text content.) If all you want is to
    draw a simple line of text, you should call setBrush() only, and leave the
    pen unset; GraphicsSimpleTextItem's pen is by default Qt::NoPen.

    GraphicsSimpleTextItem uses the text's formatted size and the associated
    font to provide a reasonable implementation of boundingRect(), shape(),
    and contains(). You can set the font by calling setFont().

    QGraphicsSimpleText does not display rich text; instead, you can use
    QGraphicsTextItem, which provides full text control capabilities.

    \image graphicsview-simpletextitem.png

    \sa QGraphicsTextItem, QGraphicsPathItem, QGraphicsRectItem,
    QGraphicsEllipseItem, QGraphicsPixmapItem, QGraphicsPolygonItem,
    QGraphicsLineItem, {Graphics View Framework}
*/

/*!
    Constructs a GraphicsSimpleTextItem.

    \a parent is passed to QGraphicsItem's constructor.

    \sa QGraphicsScene::addItem()
*/
GraphicsItemSimpleText::GraphicsItemSimpleText(QGraphicsObject *parent)
    : GraphicsShapeItem(*new GraphicsItemSimpleTextPrivate, parent)
{
}

/*!
    Constructs a GraphicsSimpleTextItem, using \a text as the default plain text.

    \a parent is passed to QGraphicsItem's constructor.

    \sa QGraphicsScene::addItem()
*/
GraphicsItemSimpleText::GraphicsItemSimpleText(const QString &text, QGraphicsObject *parent)
    : GraphicsShapeItem(*new GraphicsItemSimpleTextPrivate, parent)
{
    setText(text);
}

/*!
    Destroys the GraphicsSimpleTextItem.
*/
GraphicsItemSimpleText::~GraphicsItemSimpleText()
{
}

/*!
    Sets the item's text to \a text. The text will be displayed as
    plain text. Newline characters ('\\n') as well as characters of
    type QChar::LineSeparator will cause item to break the text into
    multiple lines.
*/
void GraphicsItemSimpleText::setText(const QString &text)
{
    Q_D(GraphicsItemSimpleText);
    if (d->text == text)
        return;
    d->text = text;

    updateShape();

    emit textChanged(d->text);
}

/*!
    Returns the item's text.
*/
QString GraphicsItemSimpleText::text() const
{
    Q_D(const GraphicsItemSimpleText);
    return d->text;
}

/*!
    Sets the font that is used to draw the item's text to \a font.
*/
void GraphicsItemSimpleText::setFont(const QFont &font)
{
    Q_D(GraphicsItemSimpleText);
    d->font = font;

    updateShape();

    emit fontChanged(d->font);
}

/*!
    Returns the font that is used to draw the item's text.
*/
QFont GraphicsItemSimpleText::font() const
{
    Q_D(const GraphicsItemSimpleText);
    return d->font;
}


/*!
    \reimp
*/
void GraphicsItemSimpleText::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);
    Q_D(GraphicsItemSimpleText);

    painter->setFont(d->font);

    QString tmp = d->text;
    tmp.replace(QLatin1Char('\n'), QChar::LineSeparator);
    QStackTextEngine engine(tmp, d->font);

    QTextLayout layout;
    QTextEngine *eng = layout.engine();
    *eng = engine;     // TODO: changed

    QPen p;
    p.setBrush(d->m_brush);
    painter->setPen(p);
    if (d->m_pen.style() == Qt::NoPen && d->m_brush.style() == Qt::SolidPattern) {
        painter->setBrush(Qt::NoBrush);
    } else {
        QTextLayout::FormatRange range;
        range.start = 0;
        range.length = layout.text().length();
        range.format.setTextOutline(d->m_pen);
        layout.setFormats(QVector<QTextLayout::FormatRange>(1, range));
    }

    setupTextLayout(&layout);
    layout.draw(painter, QPointF(0, 0));

    if (option->state & (QStyle::State_Selected | QStyle::State_HasFocus))
        qt_graphicsItem_highlightSelected(this, painter, option);
}

/*!
    \reimp
*/
int GraphicsItemSimpleText::type() const
{
    return Type;
}

GraphicsItemSimpleText::GraphicsItemSimpleText(GraphicsItemSimpleTextPrivate &dd, QGraphicsObject *parent)
    : GraphicsShapeItem(dd, parent)
{

}
}

