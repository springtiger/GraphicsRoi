#include "backgroundsleeper.h"
#include <QDebug>

BackgroundSleeper::BackgroundSleeper(QObject *parent) : QObject(parent)
{
    funSleep = [](int i){ QThread::msleep(1); };

    connect(&m_futureWatcher, &QFutureWatcher<void>::finished, [=](){
        if (false == m_futureWatcher.future().isCanceled())
            emit regulared();
        emit finished();
    });

    connect(&m_futureWatcher, &QFutureWatcher<void>::canceled, this, &BackgroundSleeper::canceled);
}

void BackgroundSleeper::msleep(int ms)
{
    QVector<int> vector;
    for (int i = 0; i < ms; ++i)
        vector.append(i);

    m_futureWatcher.setFuture(QtConcurrent::map(vector, funSleep));
}

void BackgroundSleeper::cancel()
{
    m_futureWatcher.cancel();
    m_futureWatcher.waitForFinished();
}

