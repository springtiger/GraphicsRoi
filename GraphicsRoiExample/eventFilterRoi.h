#ifndef ROIEVENTFILTER_H
#define ROIEVENTFILTER_H

#include <QObject>
#include <QAction>

class EventFilterRoi : public QObject
{
    Q_OBJECT
public:
    EventFilterRoi(QObject *parent);
protected:
    virtual bool eventFilter(QObject *watched, QEvent *event);
protected:
    QAction *m_removeAction;
    QAction *m_rotatable   ;
    QAction *m_resizable   ;

};

#endif // ROIEVENTFILTER_H
