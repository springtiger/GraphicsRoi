#ifndef BACKGROUNDSLEEPER_H
#define BACKGROUNDSLEEPER_H

#include <QObject>
#include <QtConcurrent>
#include <functional>

class BackgroundSleeper : public QObject
{
    Q_OBJECT
public:
    explicit BackgroundSleeper(QObject *parent = nullptr);

    void msleep(int ms);
    void cancel();
signals:
    void finished();  // 结束
    void canceled();  // 取消结束
    void regulared(); // 正常结束
public slots:

private:
    QFutureWatcher<void> m_futureWatcher;
    std::function<void(int&)> funSleep;
};

#endif // BACKGROUNDSLEEPER_H
