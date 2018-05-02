#include "calibratedialog.h"
#include "ui_calibratedialog.h"
#include <mainbussniessview.h>
#include <QtSql/QSqlQueryModel>
#include <QtSql/QSqlTableModel>
#include <QtSql/QSqlRecord>
#include <QtSql/QSqlQuery>
#include <QTableView>
#include <QScrollBar>
#include <QDebug>
CalibrateDialog::CalibrateDialog(QWidget *parent, MainBussniessView* pMainView) :
    QTabWidget(parent), pMainBussView(pMainView),
    ui(new Ui::CalibrateDialog)
{
    ui->setupUi(this);
    pQueryModel = new QSqlQueryModel(this);
    pMainBussView->GetItemName(pQueryModel);
    ui->lstView_ItemName->setModel(pQueryModel);

    pTableModel = NULL;
    LanguageMananger();
    InstallDefaultLanguage();
    ui->btn_CalibrateStop->setEnabled(false);
    ui->btn_CalibrateData->setEnabled(true);
    QRegExp regx("[0-9]+$");
    validator = new QRegExpValidator(regx, this);
    ui->edt_Calibrate0->setValidator(validator);
    ui->edt_Calibrate1->setValidator(validator);
    ui->edt_Calibrate2->setValidator(validator);
    ui->edt_Calibrate3->setValidator(validator);
    ui->edt_Calibrate4->setValidator(validator);
    ui->edt_Calibrate5->setValidator(validator);
    ui->edt_Calibrate6->setValidator(validator);
    ui->edt_Calibrate7->setValidator(validator);
    /*ui->edt_LaderValue0->setValidator((validator));
    ui->edt_LaderValue1->setValidator((validator));
    ui->edt_LaderValue2->setValidator((validator));
    ui->edt_LaderValue3->setValidator((validator));
    ui->edt_LaderValue4->setValidator((validator));
    ui->edt_LaderValue5->setValidator((validator));
    ui->edt_LaderValue6->setValidator((validator));
    ui->edt_LaderValue7->setValidator((validator));
*/
    //ui->edt_BeginDate->setDateTime(QDateTime::currentDateTime());
    //ui->edt_EndDate->setDateTime(QDateTime::currentDateTime());
    connect(pMainView, SIGNAL(CalibrateObserverveResult(QSqlTableModel*)), this, SLOT(on_CalibrateObserverveResult(QSqlTableModel*)), Qt::AutoConnection);
    //connect(pMainView, SIGNAL(Test_WhiteResult(QSqlTableModel*)), this, SLOT(on_CalibrateObserverveResult(QSqlTableModel*)));

}

void CalibrateDialog::LanguageMananger(){
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
void CalibrateDialog::InstallDefaultLanguage(){

    qApp->removeTranslator(&App::translator);
    if(App::current_language == (int)QLocale::Chinese){
        App::translator.load(App::language_Chinese);
    }else {
        App::translator.load(App::language_English);
    }
    qApp->installTranslator(&App::translator);
    ui->retranslateUi(this);
}

CalibrateDialog::~CalibrateDialog()
{
    if(validator != NULL){
        delete validator;
    }
    if(pTableModel != NULL){
        delete pTableModel;
    }
    if(pQueryModel != NULL){
        delete pQueryModel;
    }
    delete ui;
}

void CalibrateDialog::on_lstView_ItemName_pressed(const QModelIndex &index)
{
    strItemName = index.data(Qt::DisplayRole).toString();
    if(pTableModel == NULL){
        pTableModel = new QSqlQueryModel(this);
    }
    int nItemNo = pMainBussView->GetItemNoByItemName(strItemName);
    pMainBussView->Calibrate_Query(pTableModel, nItemNo);
    QSqlRecord record = pTableModel->record(0);
    if(record.count() > 0){
        record.value("ItemName").toString();
        ui->edt_Calibrate0->setText(record.value("CalibrateValue0").toString());
        ui->edt_Calibrate1->setText(record.value("CalibrateValue1").toString());
        ui->edt_Calibrate2->setText(record.value("CalibrateValue2").toString());
        ui->edt_Calibrate3->setText(record.value("CalibrateValue3").toString());
        ui->edt_Calibrate4->setText(record.value("CalibrateValue4").toString());
        ui->edt_Calibrate5->setText(record.value("CalibrateValue5").toString());
        ui->edt_Calibrate6->setText(record.value("CalibrateValue6").toString());
        ui->edt_Calibrate7->setText(record.value("CalibrateValue7").toString());

        ui->edt_LaderValue0->setText(record.value("ResultValue0").toString());
        ui->edt_LaderValue1->setText(record.value("ResultValue1").toString());
        ui->edt_LaderValue2->setText(record.value("ResultValue2").toString());
        ui->edt_LaderValue3->setText(record.value("ResultValue3").toString());
        ui->edt_LaderValue4->setText(record.value("ResultValue4").toString());
        ui->edt_LaderValue5->setText(record.value("ResultValue5").toString());
        ui->edt_LaderValue6->setText(record.value("ResultValue6").toString());
        ui->edt_LaderValue7->setText(record.value("ResultValue7").toString());

    }

}

void CalibrateDialog::on_btn_CalibrateSave_clicked()
{
    CalibrateModel calibrateModel;
    int nItemNo = pMainBussView->GetItemNoByItemName(strItemName);
    calibrateModel.setItemNo(nItemNo);
    calibrateModel.setCalibrateValue0(ui->edt_Calibrate0->text().toInt());
    calibrateModel.setCalibrateValue1(ui->edt_Calibrate1->text().toInt());
    calibrateModel.setCalibrateValue2(ui->edt_Calibrate2->text().toInt());
    calibrateModel.setCalibrateValue3(ui->edt_Calibrate3->text().toInt());
    calibrateModel.setCalibrateValue4(ui->edt_Calibrate4->text().toInt());
    calibrateModel.setCalibrateValue5(ui->edt_Calibrate5->text().toInt());
    calibrateModel.setCalibrateValue6(ui->edt_Calibrate6->text().toInt());
    calibrateModel.setCalibrateValue7(ui->edt_Calibrate7->text().toInt());

    calibrateModel.setLaderValue0(ui->edt_LaderValue0->text());
    calibrateModel.setLaderValue1(ui->edt_LaderValue1->text());
    calibrateModel.setLaderValue2(ui->edt_LaderValue2->text());
    calibrateModel.setLaderValue3(ui->edt_LaderValue3->text());
    calibrateModel.setLaderValue4(ui->edt_LaderValue4->text());
    calibrateModel.setLaderValue5(ui->edt_LaderValue5->text());
    calibrateModel.setLaderValue6(ui->edt_LaderValue6->text());
    calibrateModel.setLaderValue7(ui->edt_LaderValue7->text());
    pMainBussView->Calibrate_Save(calibrateModel);
    pMainBussView->GetCalibration(nItemNo, strItemName);
}

void CalibrateDialog::on_btn_OberserveQuery_clicked()
{
    //QString strBeginDate = ui->edt_BeginDate->text();//.currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    //QString strEndDate = ui->edt_EndDate->text();//dateTime().currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    //pMainBussView->Calibrate_Observerve_Query(strBeginDate, strEndDate);
}

void CalibrateDialog::on_CalibrateObserverveResult(QSqlTableModel* calibrateTableModel){

        ui->tb_CalibrateOberserve->setModel(calibrateTableModel);
        ui->tb_CalibrateOberserve->setEditTriggers(QAbstractItemView::NoEditTriggers);   //使其不可编辑
        ui->tb_CalibrateOberserve->setSelectionMode(QAbstractItemView::SingleSelection);
        ui->tb_CalibrateOberserve->setSelectionBehavior(QAbstractItemView::SelectRows);
        //ui->tbview_TestResult->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
        ui->tb_CalibrateOberserve->verticalHeader()->hide();

}

void CalibrateDialog::on_btn_CalibrateData_clicked()
{
    QString strItemName = ui->cbb_ItemName->currentText();
    pMainBussView->Test_DeleteResult(strItemName);
    bool bResult = false;
    ui->btn_CalibrateData->setEnabled(false);
    ui->btn_CalibrateStop->setEnabled(true);
    ui->tb_CalibrateOberserve->setEnabled(false);
    bResult = pMainBussView->White(strItemName);
    if(bResult){
        ui->btn_CalibrateData->setEnabled(true);
        ui->btn_CalibrateStop->setEnabled(false);
    }
    ui->tb_CalibrateOberserve->setEnabled(true);

}

void CalibrateDialog::on_btn_CalibrateStop_clicked()
{
    bool bResult = false;
    ui->btn_CalibrateStop->setEnabled(false);
    ui->btn_CalibrateData->setEnabled(false);
    bResult = pMainBussView->Stop();
    if(bResult){
        QString strItemName = ui->cbb_ItemName->currentText();
        //ui->lb_WhiteResult->setText(QString("%1").arg(pMainBussView->WhiteCalendar(strItemName)));//calendar result
        QList<int> lstResult;
        pMainBussView->WhiteCalendar(strItemName, lstResult);
        ui->lstResultView->clear();
        foreach (int nResult, lstResult) {
            ui->lstResultView->addItem(QString("%1").arg(nResult));
        }
        int nTotalCount = pageCount(ui->tb_CalibrateOberserve);
        ui->lbTotalCount->setText(QString("%1").arg(nTotalCount));
        ui->btn_CalibrateStop->setEnabled(false);
        ui->btn_CalibrateData->setEnabled(true);
    }
}

void CalibrateDialog::on_btn_NextPage_clicked()
{

    pageDown(ui->tb_CalibrateOberserve, false);

}
bool CalibrateDialog::pageDown(QTableView *p,bool isLoop)//下翻
{
    if(p == NULL)  return false;
    if(p->rowAt(0) < 0) return false;
    int rowCount = p->model()->rowCount();
    int rowHeight = p->rowHeight(0);
    int tableViewHeight = p->height();
    int rowCountPerPage = tableViewHeight/rowHeight-1;		//每页显示行数
    int canNotViewCount = rowCount-rowCountPerPage;			//看不见的行数
    if(canNotViewCount == 0){
        return false;
    }
    int maxValue = p->verticalScrollBar()->maximum();		// 当前SCROLLER最大显示值
    if(maxValue == 0){
        return false;
    }
    int pageValue = (maxValue*rowCountPerPage)/canNotViewCount;
    int nCurScroller = p->verticalScrollBar()->value();		//获得当前scroller值
    if(nCurScroller<maxValue)
        if(rowCountPerPage > canNotViewCount){
            p->verticalScrollBar()->setSliderPosition(canNotViewCount);
        }else{
            p->verticalScrollBar()->setSliderPosition(nCurScroller+pageValue);
        }

    else
    {
        if(isLoop == TRUE)
            p->verticalScrollBar()->setSliderPosition(0);
    }
}

bool CalibrateDialog::pageHome(QTableView *p)//首页
{
    if(p == NULL)  return false;
    if(p->rowAt(0) < 0) return false;
    int maxValue = p->verticalScrollBar()->maximum(); // 当前SCROLLER最大显示值
    if(maxValue == 0)  return false;
    p->verticalScrollBar()->setSliderPosition(0);
}

bool CalibrateDialog::pageEnd(QTableView *p)//末页
{
    if(p == NULL)  return false;
    if(p->rowAt(0) < 0) return false;
    int maxValue = p->verticalScrollBar()->maximum(); // 当前SCROLLER最大显示值
    if(maxValue == 0)  return false;
    p->verticalScrollBar()->setSliderPosition(maxValue);
}

int CalibrateDialog::pageCount(QTableView *p)//QTableView 总页数
{
    if(p == NULL)  return -1;
    if(p->rowAt(0) < 0) return false;
    int rowCount = p->model()->rowCount();
    int rowHeight = p->rowHeight(0);
    int tableViewHeight = p->height();
    int rowCountPerPage = tableViewHeight/rowHeight-1;//每页显示行数
    int ret = rowCount/rowCountPerPage;
    int tem = rowCount%rowCountPerPage;
    if (tem != 0) ret++;
    return ret;
}

bool CalibrateDialog::pageTo(QTableView *p, int pageNO)//翻到指定页
{
    if(p == NULL)  return false;
    if(p->rowAt(0) < 0) return false;
    int maxPage = pageCount(p);
    if(pageNO > maxPage)  return false;
    int rowCount = p->model()->rowCount();
    int rowHeight = p->rowHeight(0);
    int tableViewHeight = p->height();
    int rowCountPerPage = tableViewHeight/rowHeight-1;		//每页显示行数
    int canNotViewCount = rowCount-rowCountPerPage;			//看不见的行数
    if(canNotViewCount == 0) return false;
    int maxValue = p->verticalScrollBar()->maximum();		// 当前SCROLLER最大显示值
    if(maxValue == 0) return false;
    int pageValue = (maxValue*rowCountPerPage)/canNotViewCount;
    p->verticalScrollBar()->setSliderPosition(pageValue*(pageNO-1));
}

bool CalibrateDialog::pageUp(QTableView *p,bool isLoop)//上翻
{
    if(p == NULL)  return false;
    if(p->rowAt(0) < 0) return false;
    int rowCount = p->model()->rowCount();
    int rowHeight = p->rowHeight(0);
    int tableViewHeight = p->height();
    int rowCountPerPage = tableViewHeight/rowHeight-1;		//每页显示行数
    int canNotViewCount = rowCount-rowCountPerPage;			//看不见的行数
    if(canNotViewCount == 0) return false;
    int maxValue = p->verticalScrollBar()->maximum();		// 当前SCROLLER最大显示值
    if(maxValue == 0) return false;
    int pageValue = (maxValue*rowCountPerPage)/canNotViewCount;
    int nCurScroller = p->verticalScrollBar()->value();		//获得当前scroller值
    if(nCurScroller>0){
        p->verticalScrollBar()->setSliderPosition(nCurScroller-pageValue);
    }
    else
    {
        if(isLoop == TRUE){
            p->verticalScrollBar()->setSliderPosition(maxValue);
        }
    }
}

void CalibrateDialog::on_btn_FirstPag_clicked()
{
    pageHome(ui->tb_CalibrateOberserve);
}

void CalibrateDialog::on_btn_PreviousPage_clicked()
{
    pageUp(ui->tb_CalibrateOberserve,false);
}

void CalibrateDialog::on_btn_LastPage_clicked()
{
    pageEnd(ui->tb_CalibrateOberserve);
}


