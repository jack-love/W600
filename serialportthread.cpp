#include "serialportthread.h"
#include"posix_qextserialport.h"
//#include "GlobalData.h"
SerialPortThread::SerialPortThread(QObject *parent) :
    QThread(parent)
{

    pSerialPort = (Posix_QextSerialPort*)parent;
    m_bStoped = false;
}
SerialPortThread::~SerialPortThread(){

}

void SerialPortThread::stop(){
    m_bStoped = true;
}


void SerialPortThread::run(){
    while(!m_bStoped){//接收数据信息
       QByteArray temp = pSerialPort->readAll();
       if(temp != ""){
           QString myStrTemp = QString::fromLatin1(temp);
            //gMutex.lock();
           //解析数据格式
           //getRecieveData.append(myStrTemp);
           //gMutex.unlock();
           //waitRecieve.wakeOne();
       }
       usleep(10);
    }

}

