#include "whitethread.h"
#include <mainbussniessview.h>
#include <qdebug.h>
#include <QDateTime>
#include <QCoreApplication>
WhiteThread::WhiteThread(QObject *parent) :
    QThread(parent), pMainBussView((MainBussniessView*)parent)
{
    App::test_finished = false;
    //App::test_result = false;
}
void WhiteThread::run(){
qDebug()<< "+++++++++++++++begin start thread+++++++++++";
    App::mutex.lock();
    bool bfinished = false;
    int nResult = 0;
    #ifndef TEST_SO
    int nSys_status = pMainBussView->Machine_Sys_Status();
    if(1 == nSys_status) //1.Machine stop
    {
        pMainBussView->Machine_Go_on();
    }
    #endif
    //qDebug()<< "+++++++++++++++begin Processing+++++++++++";
    while(!bfinished){
        bfinished = App::test_finished;
        if(bfinished){
            break;
        }
        App::test_result = false;
        nResult = pMainBussView->Machine_Run(pMainBussView->_result);
        if(1 == nResult){
            CalibrateObserverModel * resultModel = new CalibrateObserverModel();
            for(int i = 0;i < MAX_ITEM;i++){
                QString strItemName = QString(pMainBussView->_result[i].name);
                //int ncmp = strcmp(strItemName.data(), (const char*)pMainBussView->getItemName().data());
                if(strItemName == pMainBussView->getItemName()){
                    resultModel->setWhite(pMainBussView->_result[i].wrgb_value[0]);
                    resultModel->setRed(pMainBussView->_result[i].wrgb_value[1]);
                    resultModel->setGreen(pMainBussView->_result[i].wrgb_value[2]);
                    resultModel->setBlue(pMainBussView->_result[i].wrgb_value[3]);
                    resultModel->setCalibrateValue(pMainBussView->_result[i].wrgb_result_value);
                    int nItemNo = i;//pMainBussView->getItemModel().takeAt(i).getItemNo();
                    resultModel->setItemNo(nItemNo);
                    resultModel->setItemName(QString(pMainBussView->_result[i].name));
                    resultModel->setResultValue(QString(pMainBussView->_result[i].unit));
                    resultModel->setCalibrateDate(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
                    qDebug()<< "+++++++"+QString(pMainBussView->_result[i].name)+"++++++++"+QString("%1").arg(pMainBussView->_result[i].wrgb_value[0])+"++++++++++"+QString("%2").arg(pMainBussView->_result[i].wrgb_value[1])+"++++++++++++"+QString("%3").arg(pMainBussView->_result[i].wrgb_value[2])+"++++++++++++"+QString("%4").arg(pMainBussView->_result[i].wrgb_value[3])+"+++++++++++++"+QString("%5").arg(pMainBussView->_result[i].wrgb_result_value)+"++++++++";
                    break;
                }
            }

            pMainBussView->WhiteResultSave(resultModel);
            pMainBussView->Test_WhiteResult(resultModel);
            delete resultModel;
            //qDebug()<< "+++++++++++++++save and display data+++++++++++";
        }
        App::test_result = true;
        msleep(300);
    }
    qDebug()<< "+++++++++++++++end thread+++++++++++";
    App::mutex.unlock();

}

void WhiteThread::msleep(long s){
   /* QTime dieTime = QTime::currentTime().addMSecs(s);
        while(QTime::currentTime() < dieTime ){
            //QCoreApplication::processEvents(QEventLoop::AllEvents,100);
            QThread::msleep(1);
        }
        */
    QThread::msleep(s);
}
