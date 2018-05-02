#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iconhelper.h>
#include "myhelper.h"
#include <frmmessagebox.h>
#include <testingdialog.h>
#include <mainbussniessview.h>
#include <QMenu>
#include <querydialog.h>
#include <qualitycontroldialog.h>
#include <parameterdialog.h>
#include <calibratedialog.h>
#include <systemdialog.h>
#include <maintenancedialog.h>
//#include <OptionManager>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    /*QFont font  = qApp->font();
    font.setFamily("Ubuntu");
    font.setPointSize(12);
    qApp->setFont(font);
*/
    m_MainButtonDlg = NULL;
    m_TestDialog = NULL;
    m_queryDialog = NULL;
    m_qualityControlDialog = NULL;
    m_ParameterDialog = NULL;
    m_calibrateDialog = NULL;
    m_systemDialog = NULL;
    m_MaintenanceDialog = NULL;


    ui->setupUi(this);
    m_MainView = new MainBussniessView(this);
#ifndef TEST_SO
    /*    while(true){
            if(0 == m_MainView->Machine_Sys_Status()){
                myHelper::ShowMessageBoxError("System error");
            }
            else
            {
                break;
            }
        }
        */
#endif
    m_MainView->StartProcessing();
    QRect rect(500,500,800, 480);
    this->setGeometry(rect);
    //myHelper::FormInCenter(this);
    this->InitStyle();
    buttonState = MAIN_BTN;
    selectButton(buttonState);

    connect(m_MainButtonDlg, SIGNAL(on_btnTesting()), this, SLOT(TestingActionSlot()));
    connect(m_MainButtonDlg, SIGNAL(on_btn_history()), this, SLOT(HistoryActionSlot()));
    connect(m_MainButtonDlg, SIGNAL(on_btn_Quality()), this, SLOT(QualityActionSlot()));
    connect(m_MainButtonDlg, SIGNAL(on_btn_Calibrate()), this, SLOT(CalibrateActionSlot()));
    connect(m_MainButtonDlg, SIGNAL(on_btn_ItemParam()), this, SLOT(ItemActionSlot()));
    connect(m_MainButtonDlg, SIGNAL(on_btn_System()), this, SLOT(SystemActionSlot()));
    connect(m_MainButtonDlg, SIGNAL(on_btn_Debug()), this, SLOT(DebugActionSlot()));

    createAction();
    createMenu();
    createContentMenu();

    timer = new QTimer;
    connect(timer, SIGNAL(timeout()), this, SLOT(onSystemTime()));
    timer->start(1000);
    m_MainView->EndProcessing();
}
void MainWindow::LanguageMananger(){
    //translator = NULL;
    //QString lanStr = OptionManager::getInstance()->getRegConfig(OPTION_LAN_STR);

    if(0 == App::lanStr.compare("CHINESE", Qt::CaseInsensitive)){
        App::current_language = QLocale::Chinese;
    }else if(0 == App::lanStr.compare("ENGLISH", Qt::CaseInsensitive)){
        App::current_language = QLocale::English;
    }else{
        App::current_language = QLocale::system().language();
    }

}
void MainWindow::InstallDefaultLanguage(){

    qApp->removeTranslator(&App::translator);
    if(App::current_language == (int)QLocale::Chinese){
        App::translator.load(App::language_Chinese);
    }else {
        App::translator.load(App::language_English);
    }
    qApp->installTranslator(&App::translator);
    ui->retranslateUi(this);
}
void MainWindow::onSystemTime(){

    int hour = QTime::currentTime().hour();
    ui->lcdHour->display(hour);
    int minute = QTime::currentTime().minute();
    ui->lcdMinute->display(minute);
    int second = QTime::currentTime().second();
    ui->lcdSecond->display(second);

}

MainWindow::~MainWindow()
{
    if(m_MainView != NULL){
        delete m_MainView;
    }
    if(m_MaintenanceDialog != NULL){
        delete m_MaintenanceDialog;
    }
    if(m_calibrateDialog != NULL){
        delete m_calibrateDialog;
    }
    if(m_ParameterDialog != NULL){
        delete m_ParameterDialog;
    }
    if(m_qualityControlDialog != NULL){
        delete m_qualityControlDialog;
    }
    if(m_queryDialog != NULL){
        delete m_queryDialog;
    }
    if(m_TestDialog != NULL){
        delete m_TestDialog;
    }
    if(m_MainButtonDlg != NULL){
        delete m_MainButtonDlg;
    }
    delete ui;
}


void MainWindow::hideButton(MAIN_BUTTON button){
    switch(button){
        case TESTING:
            m_TestDialog->hide();
        break;
        case HISTORY:
            m_queryDialog->hide();
        break;
        case QUALITY:
            m_qualityControlDialog->hide();
        break;
        case CALIBRATE:
            m_calibrateDialog->hide();
        break;
        case ITEM:
            m_ParameterDialog->hide();
        break;
        case SYSTEM:
            m_systemDialog->hide();
        break;
        case DEBUG:
            m_MaintenanceDialog->hide();
        break;
        case MAIN_BTN:
            m_MainButtonDlg->hide();
        break;
    }
}

void MainWindow::selectButton(MAIN_BUTTON button){
    if(true == App::test_start){
        return;
    }
    switch(button){
        case TESTING:
            if(buttonState != button){
                hideButton(buttonState);
            }
            if(m_TestDialog == NULL){
                m_TestDialog = new TestingDialog(ui->frmContent, m_MainView);
            }
            m_TestDialog->setModal(true);
            m_TestDialog->show();

            buttonState = button;
        break;
        case HISTORY:
            if(buttonState != button){
                hideButton(buttonState);
            }
            if(m_queryDialog == NULL){
                m_queryDialog = new queryDialog(ui->frmContent, m_MainView);
            }
            //queryDialog->setModal(true);
            m_queryDialog->show();

            buttonState = button;
            break;
         case QUALITY:
                if(buttonState != button){
                    hideButton(buttonState);
                }
                if(m_qualityControlDialog == NULL){
                    m_qualityControlDialog = new QualityControlDialog(ui->frmContent, m_MainView);
                }
                //m_qualityControlDialog->setModal(true);
                m_qualityControlDialog->show();

                buttonState = button;
        break;
        case CALIBRATE:
               if(buttonState != button){
                   hideButton(buttonState);
               }
               if(m_calibrateDialog == NULL){
                   m_calibrateDialog = new CalibrateDialog(ui->frmContent, m_MainView);
               }
               //m_calibrateDialog->setModal(true);
               m_calibrateDialog->show();

               buttonState = button;
       break;
        case ITEM:
            if(buttonState != button){
                hideButton(buttonState);
            }
            if(m_ParameterDialog == NULL){
                m_ParameterDialog = new ParameterDialog(ui->frmContent, m_MainView);
            }
            //m_ParameterDialog->setModal(true);
            m_ParameterDialog->show();

            buttonState = button;
            break;

        case SYSTEM:
            if(buttonState != button){
                hideButton(buttonState);
            }
            if(m_systemDialog == NULL){
                m_systemDialog = new SystemDialog(ui->frmContent, m_MainView);
            }
            //m_ParameterDialog->setModal(true);
            m_systemDialog->show();

            buttonState = button;
            break;
        case DEBUG:
            if(buttonState != button){
                hideButton(buttonState);
            }
            if(m_MaintenanceDialog == NULL){
                m_MaintenanceDialog = new MaintenanceDialog(ui->frmContent);
            }
            m_MaintenanceDialog->setModal(true);
            m_MaintenanceDialog->show();

            buttonState = button;
            break;
        case MAIN_BTN:
            if(buttonState != button){
                hideButton(buttonState);
            }
            if(m_MainButtonDlg == NULL){
                m_MainButtonDlg = new MainButtonDialog(ui->frmContent);
            }
            m_MainButtonDlg->setModal(true);
            m_MainButtonDlg->show();
            buttonState = button;
            break;
    }
}

void MainWindow::InitStyle()
{
    //设置窗体标题栏隐藏
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint);
    location = this->geometry();
    max = false;
    mousePressed = false;

    //安装事件监听器,让标题栏识别鼠标双击
    //ui->lab_SystemTitle->installEventFilter(this);

    //ui->lab_SystemTitle->setText(tr("长春万成生物电子工程公司"));
    //ui->lab_SysTime->setText(tr("2017-06-14 15:11:20"));
    IconHelper::Instance()->SetIcon(ui->btn_Close, QChar(0xf00d), 24);
    //IconHelper::Instance()->SetIcon(ui->btn_Max, QChar(0xf096), 24);
    //IconHelper::Instance()->SetIcon(ui->btnMenu_Min, QChar(0xf068), 10);
    IconHelper::Instance()->SetIcon(ui->btn_Menu, QChar(0xf0c9), 24);
    //IconHelper::Instance()->SetIcon(ui->lab_Icon, QChar(0xf015), 48);
}



bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonDblClick) {
        this->on_btn_Max_clicked();
        return true;
    }
    return QObject::eventFilter(obj, event);
}

void MainWindow::mouseMoveEvent(QMouseEvent *e)
{
    /*if (mousePressed && (e->buttons() && Qt::LeftButton) && !max) {
        this->move(e->globalPos() - mousePoint);
        e->accept();
    }*/
}

void MainWindow::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton) {
        mousePressed = true;
        mousePoint = e->globalPos() - this->pos();
        e->accept();
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *)
{
    mousePressed = false;
}


void MainWindow::on_btn_Max_clicked()
{
    /*if (max) {
        this->setGeometry(location);
        IconHelper::Instance()->SetIcon(ui->btn_Max, QChar(0xf096), 10);
        ui->btn_Max->setToolTip(tr("最大化"));
    }else {
        location = this->geometry();
        this->setGeometry(qApp->desktop()->availableGeometry());
        IconHelper::Instance()->SetIcon(ui->btn_Max, QChar(0xf079), 10);
        ui->btn_Max->setToolTip(tr("还原"));
    }
        max = !max;
        */
}

void MainWindow::createAction()
{
    QFont font;
    font.setPixelSize(35);

   //创建打开文件动作
   testingAction = new QAction(QIcon(tr(":image/Testing.png")), QString::fromLocal8Bit(" &测试"), this);
   testingAction->setFont(font);

   //关联打开文件动作的信号和槽
   connect(testingAction, SIGNAL(triggered()), this, SLOT(TestingActionSlot()));

   historyAction = new QAction(QIcon(tr(":image/History.png")), QString::fromLocal8Bit(" &历史"), this);
   historyAction->setFont(font);
   connect(historyAction, SIGNAL(triggered()), this, SLOT(HistoryActionSlot()));

   qualityAction = new QAction(QIcon(tr(":image/QualityControl.png")), QString::fromLocal8Bit(" &质控"), this);
   qualityAction->setFont(font);
   connect(qualityAction, SIGNAL(triggered()), this, SLOT(QualityActionSlot()));

   calibrateAction = new QAction(QIcon(tr(":image/Calibrate.png")), QString::fromLocal8Bit(" &校准"), this);
   calibrateAction->setFont(font);
   connect(calibrateAction, SIGNAL(triggered()), this, SLOT(CalibrateActionSlot()));

   //创建打开文件动作
   itemAction = new QAction(QIcon(tr(":image/Parameter.png")), QString::fromLocal8Bit(" &参数"), this);
   itemAction->setFont(font);
   connect(itemAction, SIGNAL(triggered()), this, SLOT(ItemActionSlot()));

   systemAction = new QAction(QIcon(tr(":image/System.png")), QString::fromLocal8Bit(" &系统"), this);
   systemAction->setFont(font);
   connect(systemAction, SIGNAL(triggered()), this, SLOT(SystemActionSlot()));

   debugAction = new QAction(QIcon(tr(":image/Maintainance.png")), QString::fromLocal8Bit(" &维护"), this);
   debugAction->setFont(font);
   connect(debugAction, SIGNAL(triggered()), this, SLOT(DebugActionSlot()));

   mainAction = new QAction(QIcon(tr(":image/Manual.png")), QString::fromLocal8Bit(" &主界面"), this);
   mainAction->setFont(font);
   connect(mainAction, SIGNAL(triggered()), this, SLOT(MainActionSolt()));
}
void MainWindow::createMenu()
{
   /************************************************************************
    * menuBar第一次被调用时QMainWindow会产生一个QMenuBar在窗体上，且返回一个QMenu的指针
    * menuBar()->addMenu()会生成一个QMenu且返回他的指针
    * QMenu加入一个QAction, 就可以对事件进行反应了
    * 一个QAction可以被多个地方使用, 与Java的Action一样
    **************************************************************************/
   menu = new QMenu();
   //menu->setFixedSize(200, 100);
   menu->setStyleSheet("background-color: rgb(200, 155, 152)");
   menu->addAction(testingAction);
   menu->addAction(historyAction);
   menu->addAction(qualityAction);
   menu->addAction(calibrateAction);
   menu->addAction(itemAction);
   menu->addAction(systemAction);
   menu->addAction(debugAction);
   menu->addAction(mainAction);
}
void MainWindow::createContentMenu()
{

    //ui->btn_Menu->setStyleSheet("QPushButton::menu-indicator{image:image/question.png;}");
    ui->btn_Menu->setContextMenuPolicy(Qt::ActionsContextMenu);
    ui->btn_Menu->setMenu(menu);
   //设置如何显示上下文菜单
}

void MainWindow::on_btn_Close_clicked()
{
    int nResult = myHelper::ShowMessageBoxQuesion(tr("是否关闭系统?"));

    if(nResult){
#ifndef TEST_SO
        m_MainView->Machine_Power();//Power off
        //close();
#endif
        //halt -p
        //system("poweroff");
        QProcess::execute(QString("poweroff"));
    }
}

void MainWindow::TestingActionSlot(){
    selectButton(TESTING);
}

void MainWindow::HistoryActionSlot(){
    selectButton(HISTORY);
}

void MainWindow::QualityActionSlot(){
    selectButton(QUALITY);
}

void MainWindow::CalibrateActionSlot(){
    selectButton(CALIBRATE);
}

void MainWindow::ItemActionSlot(){
    selectButton(ITEM);
}


void MainWindow::SystemActionSlot(){
    selectButton(SYSTEM);
}

void MainWindow::DebugActionSlot(){
    selectButton(DEBUG);
}

void MainWindow::MainActionSolt(){
    selectButton(MAIN_BTN);
}

void MainWindow::on_btn_Zh_En_clicked()
{
    if(App::lanStr == "CHINESE"){
        App::lanStr = "ENGLISH";
    }else if(App::lanStr == "ENGLISH"){
        App::lanStr = "CHINESE";
    }
    LanguageMananger();
    InstallDefaultLanguage();

}

