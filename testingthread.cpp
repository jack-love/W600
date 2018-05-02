#include "testingthread.h"
#include <mainbussniessview.h>
#include<qdatetime.h>
#include <App.h>
#include <QtDebug>
TestingThread::TestingThread(QObject *parent) :
    QThread(parent), pMainView((MainBussniessView*)parent)
{
    App::test_finished = false;
    //App::test_result = false;
    //App::bStop = -1;
}

void TestingThread::run(){
    bool bfinished = false;

#ifndef TEST_SO
    int nSys_status = pMainView->Machine_Sys_Status();
    if(1 == nSys_status) //1.Machine stop
    {
        pMainView->Machine_Go_on();
    }

#endif
    while(!bfinished){
        bfinished = App::test_finished;
        if(bfinished){
            break;
        }
        App::mutex.lock();
        int nResult = 0;
        qDebug() << "+++++++++++++++++++++++++Run++++++++++++++++++++++++++";
        App::test_result = false;
        nResult = pMainView->Machine_Run(pMainView->_result);
        if(1 == nResult){
            pMainView->GetTestResult(pMainView->_result);
            pMainView->ShowTestResult();
            qDebug() << "Show result:" + QString(pMainView->_result[0].name) + QString(pMainView->_result[0].unit) + QString(pMainView->_result[0].position);
        }
        App::mutex.unlock();
        App::test_result = true;
        msleep(300);
    }

}
void TestingThread::msleep(long s){
    QThread::msleep(s);
}

TestingThread::~TestingThread(){

}
