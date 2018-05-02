#ifndef SERIALPORTTHREAD_H
#define SERIALPORTTHREAD_H
#include<QWaitCondition>
#include <QThread>

class Posix_QextSerialPort;
class SerialPortThread : public QThread
{
    Q_OBJECT
public:
    explicit SerialPortThread(QObject *parent = 0);
    ~SerialPortThread();
    void stop();

protected:
    virtual void run() ;

signals:

public slots:
private:
    bool m_bStoped;
    Posix_QextSerialPort *pSerialPort;
};

#endif // SERIALPORTTHREAD_H
