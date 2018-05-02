#ifndef WHITETHREAD_H
#define WHITETHREAD_H

#include <QThread>
//#include <hashtable.h>
class MainBussniessView;
class WhiteThread : public QThread
{
    Q_OBJECT
public:
    explicit WhiteThread(QObject *parent = 0);
    void msleep(long s);
signals:

public slots:
protected:
        void run();
private:
        MainBussniessView* pMainBussView;
        //HashTable<int, QString> tableItem;
};

#endif // WHITETHREAD_H
