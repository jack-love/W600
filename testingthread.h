#ifndef TESTINGTHREAD_H
#define TESTINGTHREAD_H

#include <QThread>

class MainBussniessView;


class TestingThread : public QThread
{
    Q_OBJECT
public:
    explicit TestingThread(QObject *parent = 0);
    static void msleep(long s);
    //bool test_finished;
    ~TestingThread();
protected:
    void run();
signals:

public slots:

private:


    MainBussniessView *pMainView;
};

#endif // TESTINGTHREAD_H
