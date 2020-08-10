#ifndef GRAPHICSANCHORPRIVATE_H
#define GRAPHICSANCHORPRIVATE_H

#include <QGraphicsDropShadowEffect>

#include "graphicsItemPoint_p.h"
#include "graphicsAnchor.h"

class GraphicsAnchorPrivate : public GraphicsItemPointPrivate
{
    Q_DECLARE_PUBLIC(GraphicsAnchor)
public:
    GraphicsAnchorPrivate()
        : GraphicsItemRectPrivate()
        , m_actionMode(GraphicsAnchor::EdgeMove)
        , m_antialiasing(false)
        , m_polyIndex(-1)
    {
        m_effect = new QGraphicsDropShadowEffect;
        m_effect->setBlurRadius(15);
        m_effect->setOffset(0);
        m_effect->setColor(Qt::red);
        m_effect->setEnabled(false);
    }

public:
    virtual void updateShapePath() const override;
public:
    int m_positionFlag;
    GraphicsAnchor::ActionMode m_actionMode;
    QGraphicsDropShadowEffect *m_effect;
    bool m_antialiasing;
    int m_polyIndex;
};

#endif // GRAPHICSANCHORPRIVATE_H
