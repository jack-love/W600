#include "testingdialog.h"
#include "ui_testingdialog.h"
//#include <databasehelper.h>
#include <mainbussniessview.h>
#include <QSqlTableModel>
//#include <patientmodel.h>
#include <QDateTime>
#include <myhelper.h>

//
TestingDialog::TestingDialog(QWidget *parent, MainBussniessView*pMainBussniessView) :
    QDialog(parent), pMainView(pMainBussniessView),
    ui(new Ui::TestingDialog)
{
    ui->setupUi(this);

    this->setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
    QPoint point(0, 0);
    this->move(point);
    connect(pMainView, SIGNAL(testResult(QSqlTableModel*)), this, SLOT(on_TestResult(QSqlTableModel*)),Qt::AutoConnection);
    connect(pMainView, SIGNAL(positionStatus(uint)), this, SLOT(on_PositionStatus(uint)), Qt::QueuedConnection);
    connect(pMainView, SIGNAL(patientInfo(PatientModel)), this, SLOT(on_patientInfo(PatientModel)));
    //connect(this, SIGNAL(testStop()), pMainView, SLOT(on_testStop()), Qt::QueuedConnection);
    //connect(this, SIGNAL(testStart()), pMainView, SLOT(on_testStart()), Qt::QueuedConnection);
    //pMainView->InitalParameter();
    //pMainView->Query_SampleResult(1, tr("2017-11-1"), tr("2017-11-13"));
    ui->btn_Stop->setEnabled(false);
    LanguageMananger();
    InstallDefaultLanguage();
#ifdef TEST_SO
    bSerialPort = serialPort.Inital();
#endif
    QRegExp regx("[0-9]+$");
    validator = new QRegExpValidator(regx, this);
    ui->edt_SampleNo->setValidator( validator );
    ui->edt_Age->setValidator( validator );
    m_SampleNo = 0;
    memset(PrintData, 0, sizeof(PrintData));
}

void TestingDialog::LanguageMananger(){
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

void TestingDialog::InstallDefaultLanguage(){

    qApp->removeTranslator(&App::translator);
    if(App::current_language == (int)QLocale::Chinese){
        App::translator.load(App::language_Chinese);
    }else {
        App::translator.load(App::language_English);
    }
    qApp->installTranslator(&App::translator);
    ui->retranslateUi(this);
}


TestingDialog::~TestingDialog()
{
    if(validator != NULL){
        delete validator;
    }
    delete ui;
}

void TestingDialog::on_btn_Start_clicked()
{
    bool bResult = false;
    ui->btn_Stop->setEnabled(true);
    ui->btn_Start->setEnabled(false);
    ui->tbview_TestResult->setEnabled(false);
    bResult = pMainView->Start();
    if(bResult){
        ui->btn_Start->setEnabled(true);
    }
    ui->tbview_TestResult->setEnabled(true);
}

void TestingDialog::on_btn_Stop_clicked()
{
    bool bResult = false;
    ui->btn_Stop->setEnabled(false);
    ui->btn_Start->setEnabled(false);

    bResult = pMainView->Stop();
    if(bResult){
        ui->btn_Stop->setEnabled(false);
        ui->btn_Start->setEnabled(true);
    }else {
        ui->btn_Stop->setEnabled(true);
        ui->btn_Start->setEnabled(false);
    }
}

bool TestingDialog::on_TestResult(QSqlTableModel* model){
    ui->tbview_TestResult->setModel(model);
    ui->tbview_TestResult->setEditTriggers(QAbstractItemView::NoEditTriggers);   //使其不可编辑

    ui->tbview_TestResult->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tbview_TestResult->setSelectionBehavior(QAbstractItemView::SelectRows);
    //ui->tbview_TestResult->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    ui->tbview_TestResult->verticalHeader()->hide();
    return false;
}

bool TestingDialog::on_PositionStatus(uint iPos){

    ui->pos_1->setStyleSheet("background-color: rgb(221, 255, 252)");
    ui->pos_2->setStyleSheet("background-color: rgb(221, 255, 252)");
    ui->pos_3->setStyleSheet("background-color: rgb(221, 255, 252)");
    ui->pos_4->setStyleSheet("background-color: rgb(221, 255, 252)");
    ui->pos_5->setStyleSheet("background-color: rgb(221, 255, 252)");
    ui->pos_6->setStyleSheet("background-color: rgb(221, 255, 252)");
    ui->pos_7->setStyleSheet("background-color: rgb(221, 255, 252)");
    ui->pos_8->setStyleSheet("background-color: rgb(221, 255, 252)");
    ui->pos_9->setStyleSheet("background-color: rgb(221, 255, 252)");
    ui->pos_10->setStyleSheet("background-color: rgb(221, 255, 252)");
    ui->pos_11->setStyleSheet("background-color: rgb(221, 255, 252)");
    ui->pos_12->setStyleSheet("background-color: rgb(221, 255, 252)");
    ui->pos_13->setStyleSheet("background-color: rgb(221, 255, 252)");

    if((iPos & 0x1000) >> 12 ){
        ui->pos_1->setStyleSheet("background-color: rgb(255, 0, 0)");
    }
    if((iPos & 0x0800)>> 11) {
        ui->pos_2->setStyleSheet("background-color: rgb(255, 0, 0)");
    }
    if((iPos & 0x0400 )>> 10){
        ui->pos_3->setStyleSheet("background-color: rgb(255, 0, 0)");
    }
    if((iPos & 0x0200) >> 9)  {
        ui->pos_4->setStyleSheet("background-color: rgb(255, 0, 0)");
    }
    if((iPos & 0x0100)>> 8){
        ui->pos_5->setStyleSheet("background-color: rgb(255, 0, 0)");
    }
    if((iPos & 0x0080)>> 7) {
        ui->pos_6->setStyleSheet("background-color: rgb(255, 0, 0)");
    }
    if((iPos & 0x0040)>>6){
        ui->pos_7->setStyleSheet("background-color: rgb(255, 0, 0)");
    }
    if((iPos & 0x0020)>>5)  {
        ui->pos_8->setStyleSheet("background-color: rgb(0, 0, 255)");
    }
    if((iPos & 0x0010)>>4){
        ui->pos_9->setStyleSheet("background-color: rgb(255, 0, 0)");
    }
    if((iPos & 0x0008)>>3)  {
        ui->pos_10->setStyleSheet("background-color: rgb(255, 0, 0)");
    }
    if((iPos & 0x0004)>>2)  {
        ui->pos_11->setStyleSheet("background-color: rgb(255, 0, 0)");
    }
    if((iPos & 0x0002)>>1){
        ui->pos_12->setStyleSheet("background-color: rgb(255, 0, 0)");
    }
    if(iPos & 0x0001)  {
        ui->pos_13->setStyleSheet("background-color: rgb(255, 0, 0)");
    }
    return false;
}

void TestingDialog::on_btn_testSave_clicked()
{
    PatientModel model;
    model.setSampleNo(ui->edt_SampleNo->text().toInt());
    model.setName(ui->edt_Name->text());
    model.setAge(ui->edt_Age->text().toInt());
    model.setSex(ui->cmb_Sex->currentIndex());
    model.setRegisterDateTime(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
    pMainView->PatientSaveAndUpdate(model);
}

void TestingDialog::on_btn_testDelete_clicked()
{
    //int curRow=ui->tbview_TestResult->currentIndex().row();//选中行
    pMainView->PatientDelete(nRow);
}

void TestingDialog::on_tbview_TestResult_pressed(const QModelIndex &index)
{
    nRow = index.row();

}

void TestingDialog::on_edt_SampleNo_returnPressed()
{
    m_SampleNo = ui->edt_SampleNo->text().toInt();
    pMainView->PatientBySampleNo(m_SampleNo);
}
void TestingDialog::on_patientInfo(PatientModel patientModel){
    ui->edt_Name->setText(patientModel.getName());
    ui->edt_Age->setText(QString("%1").arg(patientModel.getAge()));
    ui->cmb_Sex->setCurrentIndex(patientModel.getSex());
}

void TestingDialog::on_btn_Reset_clicked()
{
    pMainView->Machine_Go_on();
}

void TestingDialog::on_btn_testPrint_clicked()
{

#ifdef TEST_SO
    if(bSerialPort){
        serialPort.Write();
    }else{
        qDebug() << "Write fail /r/n";
    }
#endif
   /* if(m_SampleNo <= 0){
        myHelper::ShowMessageBoxError(tr("请输入样本号!"));
        return;
    }

    QString strWhere = QObject::tr(" where SampleNo = %1 and SampleDate == '%2'").arg(m_SampleNo).arg(QDateTime::currentDateTime().toString("yyyy-MM-dd"));
    QList<TestResultModel*> lstTestResultModel = pMainView->QueryTestResult(strWhere);
    int iCount = lstTestResultModel.count();
    if(iCount > 0){
        QString strSampleNo = "SAMPLE NO. :" + QString(lstTestResultModel.at(0)->getSampleNo()) ;
        strcpy(PrintData[0], (char*)strSampleNo.data());
        QString strDateTime = "DATE TIME :" + lstTestResultModel.at(1)->getSampleDate();
        strcpy(PrintData[1], (char*)strDateTime.data());

        for (int i = 2;i < iCount;i++) {
            QString strItem = lstTestResultModel.at(i)->getItemName() + ":"+ QString(lstTestResultModel.at(i)->getSampleValue()) + lstTestResultModel.at(i)->getUnit();
            strcpy(PrintData[i], (char*)strItem.data());
        }
}
    m_SampleNo = 0;
    */
    /*PatientModel patient;
    patient.setSampleNo(ui->edt_SampleNo->text().toInt());
    patient.setName(ui->edt_Name->text());
    patient.setAge(ui->edt_Age->text().toInt());
    patient.setSex(ui->cmb_Sex->currentText().toInt());
    pMainView->PrintInformation(patient);
    strcpy(report.sampleNo, "0001");
    strcpy(report.item_result[0].itemName, "WBC");
    */
}
