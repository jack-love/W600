#include "stopthread.h"
#include <App.h>
#include <qdebug.h>
#include <mainbussniessview.h>
StopThread::StopThread(QObject *parent) :
    QThread(parent), pMainView((MainBussniessView*)parent)
{

}
void StopThread::run(){
    //qDebug()<< "++++++++++++++++++++++stop thread+++++++++++++++++++++";
    int nResult = 0;
#ifndef TEST_SO
    //int nSys_status = pMainView->Machine_Sys_Status();
    //if(0 <= nSys_status) //2.Machine Action
    //{

    while ((nResult == 0)){
        nResult = pMainView->Machine_Stop();
    }

    //}
    //qDebug() << "+++++++++++++++++++++" + QString("%1").arg(bResult) + "+++++++++++++++++++";
#endif
}

void StopThread::msleep(long s){
    QThread::msleep(s);
}
