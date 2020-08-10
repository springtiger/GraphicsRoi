#include "interfaceRoi.h"

#include <QObject>
#include <QDebug>
#include <QGraphicsScene>

#define LENGTH 9

IRoi::IRoi(GraphicsShapeItem *roi)
    : m_colorAnchorBorde(QColor(153, 204, 255, 200).dark())
    , m_colorAnchorFill (QColor(153, 204, 255, 200))
    , m_bAnchorAutoHide(false)
//    , m_pRoi(roi)
{
//    Q_ASSERT(m_pRoi != 0);

    //    init();
}

bool IRoi::centreVisible()
{
    return m_bCentreVisible;
}

bool IRoi::rotatable()
{
    return m_bRotatable;
}

bool IRoi::resizable()
{
    return m_bResizable;
}
