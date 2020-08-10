#include "eventFilterRoi.h"
#include <QEvent>
#include <QDebug>
#include <QGraphicsItem>
#include <QMenu>
#include <QGraphicsScene>
#include <QGraphicsSceneContextMenuEvent>
#include "interfaceRoi.h"


EventFilterRoi::EventFilterRoi(QObject *parent)
    : QObject(parent)
    , m_removeAction(0)
    , m_rotatable   (0)
    , m_resizable   (0)

{
    m_removeAction = new QAction(tr("Remove"), this);

    m_rotatable = new QAction(tr("Rotatable"), this);
    m_rotatable->setCheckable(true);

    m_resizable = new QAction(tr("Resizable"), this);
    m_resizable->setCheckable(true);
}

bool EventFilterRoi::eventFilter(QObject *watched, QEvent *event)
{
    switch (event->type())
    {
    case QEvent::ContextMenu:
        qDebug() << "RoiEventFilter::QEvent::ContextMenu";
        break;
    case QEvent::GraphicsSceneContextMenu:
    {
        QGraphicsSceneContextMenuEvent *sceneEvent = static_cast<QGraphicsSceneContextMenuEvent *>(event);
        IRoi *iRoi = qobject_cast<IRoi*>(watched);
        QGraphicsItem *item = qobject_cast<QGraphicsItem*>(watched);

        QMenu menu;

        menu.addAction(m_removeAction);

        if (iRoi)
        {
            m_rotatable->setChecked(iRoi->rotatable());
            menu.addAction(m_rotatable);

            m_resizable->setChecked(iRoi->resizable());
            menu.addAction(m_resizable);
        }

        QAction *selectedAction = menu.exec(sceneEvent->screenPos());
        if (selectedAction == m_removeAction)
        {
            // Note: It is more efficient to remove the item from the QGraphicsScene before destroying the item.
            item->scene()->removeItem(item);
            delete item;
            return true;
        }
        else if (selectedAction == m_rotatable)
        {
            iRoi->setRotatable(m_rotatable->isChecked());
        }
        else if (selectedAction == m_resizable)
        {
            iRoi->setResizable(m_resizable->isChecked());
        }
    }
        break;
    default:
        break;
    }
    return QObject::eventFilter(watched, event);
}


