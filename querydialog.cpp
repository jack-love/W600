#include "querydialog.h"
#include "ui_querydialog.h"
#include <myhelper.h>
#include <mainbussniessview.h>
#include <QtSql/QSqlTableModel>
#include <QtSql/QSqlRecord>
#include <QtSql/QSqlQueryModel>
queryDialog::queryDialog(QWidget *parent, MainBussniessView*pMainBussniessView) :
    QTabWidget(parent),pMainView(pMainBussniessView),
    ui(new Ui::queryDialog)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
    QPoint point(0, 0);
    this->move(point);
    connect(pMainView, SIGNAL(PatientResult(QSqlTableModel*)), this, SLOT(on_PatientResult(QSqlTableModel*)));
    connect(pMainView, SIGNAL(SampleResult(QSqlTableModel*)), this, SLOT(on_SampleResult(QSqlTableModel*)));
    connect(pMainView, SIGNAL(QuerySampleResult(QSqlTableModel*)), this, SLOT(on_QuerySampleResult(QSqlTableModel*)));
    ui->dt_query_Start->setDateTime(QDateTime::currentDateTime());
    ui->dt_query_End->setDateTime(QDateTime::currentDateTime());
    ui->dt_query_Start_2->setDateTime(QDateTime::currentDateTime());
    ui->dt_query_End_2->setDateTime(QDateTime::currentDateTime());
    itemTableModel = new QSqlQueryModel(this);
    pMainBussniessView->GetItemName(itemTableModel);
    ui->cb_ItemName->setModel(itemTableModel);
    LanguageMananger();
    InstallDefaultLanguage();
}

void queryDialog::LanguageMananger(){
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
void queryDialog::InstallDefaultLanguage(){

    qApp->removeTranslator(&App::translator);
    if(App::current_language == (int)QLocale::Chinese){
        App::translator.load(App::language_Chinese);
    }else {
        App::translator.load(App::language_English);
    }
    qApp->installTranslator(&App::translator);
    ui->retranslateUi(this);
}
queryDialog::~queryDialog()
{
    delete itemTableModel;
    delete ui;
}

void queryDialog::on_btn_query_date_clicked()
{

    if(!ui->ck_query_setting->isChecked()){
        myHelper::ShowMessageBoxError(QObject::tr("不允许为空"));
        return;
    }

    int sampleNo = ui->edt_query_SampleNo->text().toInt();
    QString sBeginDate = ui->dt_query_Start->dateTime().toString("yyyy-MM-dd hh:mm:ss");
    QString sEndDate = ui->dt_query_End->dateTime().toString("yyyy-MM-dd hh:mm:ss");
    pMainView->Query_DateBySampleNoAndDate(sampleNo, sBeginDate, sEndDate);
}

void queryDialog::on_PatientResult(QSqlTableModel*model){
    patientModel = model;
    ui->tablevew_Patient->setModel(model);
    ui->tablevew_Patient->setEditTriggers(QAbstractItemView::NoEditTriggers);   //使其不可编辑

    ui->tablevew_Patient->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tablevew_Patient->setSelectionBehavior(QAbstractItemView::SelectRows);
    //ui->tablevew_Patient->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    ui->tablevew_Patient->verticalHeader()->hide();
}

void queryDialog::on_SampleResult(QSqlTableModel* testModel){


    ui->tableView_TestResult->setModel(testModel);
    ui->tableView_TestResult->setEditTriggers(QAbstractItemView::NoEditTriggers);   //使其不可编辑

    ui->tableView_TestResult->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView_TestResult->setSelectionBehavior(QAbstractItemView::SelectRows);
    //ui->tablevew_Patient->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    ui->tableView_TestResult->verticalHeader()->hide();
    //delete testModel;
}

void queryDialog::on_tablevew_Patient_pressed(const QModelIndex &index)
{
    nRow = index.row();
    QSqlRecord record = patientModel->record(nRow);
    if(record.count() > 0){
        int nSampleNo = record.value("SampleNo").toInt();
        QString strDateTime = record.value("RegisterDate").toString();
        QString tempDate = strDateTime;
        QString sEndDate = tempDate.replace(10, 9, " 23:59:59");
        pMainView->Query_SampleResult(nSampleNo, strDateTime, sEndDate);
    }
}

void queryDialog::on_btn_ItemQuery_clicked()
{
    QString strItemName = ui->cb_ItemName->currentText();
    if(strItemName == ""){
        myHelper::ShowMessageBoxInfo(QObject::tr("项目不允许为空"));
        return;
    }
    QString sBeginDate_2 = ui->dt_query_Start_2->dateTime().toString("yyyy-MM-dd hh:mm:ss");
    QString sEndDate_2 = ui->dt_query_End_2->dateTime().toString("yyyy-MM-dd hh:mm:ss");
    int nItemNo = pMainView->GetItemNoByItemName(strItemName);
    pMainView->Query_TestResult(nItemNo, sBeginDate_2, sEndDate_2);
}

void queryDialog::on_QuerySampleResult(QSqlTableModel* testModel){
    ui->tbView_SampleResult->setModel(testModel);
    ui->tbView_SampleResult->setEditTriggers(QAbstractItemView::NoEditTriggers);   //使其不可编辑

    ui->tbView_SampleResult->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tbView_SampleResult->setSelectionBehavior(QAbstractItemView::SelectRows);
    //ui->tablevew_Patient->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    ui->tbView_SampleResult->verticalHeader()->hide();
}
