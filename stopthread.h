#ifndef STOPTHREAD_H
#define STOPTHREAD_H

#include <QThread>
class MainBussniessView;
class StopThread : public QThread
{
    Q_OBJECT
public:
    explicit StopThread(QObject *parent = 0);
    void msleep(long s);
signals:

public slots:
private:
    MainBussniessView *pMainView;
protected:
    void run();
};

#endif // STOPTHREAD_H
