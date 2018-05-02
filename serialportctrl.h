#ifndef SERIALPORTCTRL_H
#define SERIALPORTCTRL_H

#include <QObject>
class Posix_QextSerialPort;
class SerialPortThread;
class SerialPortCtrl : public QObject
{
    Q_OBJECT
public:
    explicit SerialPortCtrl(QObject *parent = 0);
    bool Inital();
    void Write();
    void Config();
    void Close();

signals:

public slots:

private:
    Posix_QextSerialPort *pSerialPort;
    SerialPortThread * pSerialPortThread;
};

#endif // SERIALPORTCTRL_H
