#include "serialportctrl.h"
#include"posix_qextserialport.h"
#include<serialportthread.h>
#include <QMessageBox>
#include <qtextcodec.h>
#include <QByteArray>
#include <qdebug.h>
#include <QCoreApplication>
SerialPortCtrl::SerialPortCtrl(QObject *parent) :
    QObject(parent)
{
    pSerialPort = new Posix_QextSerialPort();

}
bool SerialPortCtrl::Inital(){
    bool bResult = false;
    pSerialPort = new Posix_QextSerialPort("/dev/ttyS1", QextSerialBase::Polling);
    bool bOpen = pSerialPort->open(QIODevice::ReadWrite);
     if(bOpen){
        pSerialPort->setBaudRate(BAUD115200);
        pSerialPort->setDataBits(DATA_8);
        pSerialPort->setParity(PAR_NONE);
        pSerialPort->setStopBits(STOP_1);
        pSerialPort->setFlowControl(FLOW_OFF);
        pSerialPort->setTimeout(200);
        /*readTimer = new QTimer(this);
        readTimer->start(100);
        connect(readTimer, SIGNAL(timeout()), this, SLOT(readMyCom()));
        */

        pSerialPortThread = new SerialPortThread(pSerialPort);
        pSerialPortThread->start();
        bResult = true;
        qDebug() << "serial port open successfull\r\n";
        }else{
            QMessageBox::information(NULL, tr("tip"), tr("open serialport fail!"));
        }
    return bResult;
}

void SerialPortCtrl::Write(){

    QTextCodec *codec = QTextCodec::codecForName("GBK"); //建立一个unicode与GBK之间的转换器
    QByteArray bytesForGBK = codec->fromUnicode(" 日    期: *+-         \r\n 诊    号: 123456 \r\n 胆红素  :  00000   umol/L  \r\n 酮体    :  00000   mmol/L  \r\n 血      :  00000 cells/uL  \r\n 蛋白质  :  5.0        g/L  \r\n 亚硝酸盐:  00000           \r\n 白细胞  :  0.000 cells/uL  \r\n 葡萄糖  :  00000   mmol/L  \r\n 比重    :  1.005           \r\n 酸碱度  :  00000           \r\n 抗坏血酸:  00000   mmol/L  \r\n 微白蛋白:  00000     mg/L  \r\n 肌    酐:  00000   mmol/L  \r\n 钙 离 子:  00000   mmol/L \r\n");
    pSerialPort->write(bytesForGBK);
    /*int i = 0;
    while (i < 10) {
        QByteArray  data;
            data[0] = 0x55;
            data[1] = 0xaa;
            data[2] = 0x55;
            data[3] = 0xaa;
            data[4] = 0x05;
            data[5] = 0x01;
            data[6] = 0x01;
            data[7] = 0x55;
            data[8] = 0xaa;
            data[9] = 0x55;
            data[10] = 0xaa;
            pSerialPort->write(data.data());
            qDebug() << "write data!";
            i++;
        QCoreApplication::processEvents(QEventLoop::AllEvents, 500);
    }
    */
    /*QByteArray  data;
    data[0] = 0xff;
    data[1] = 0x11;
    pSerialPort->write(data.data());
    */
}

void SerialPortCtrl::Config(){

}

void SerialPortCtrl::Close(){
    pSerialPort->close();
    delete pSerialPort;
    delete pSerialPortThread;
}
