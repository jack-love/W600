#include "qualitycontroldialog.h"
#include "ui_qualitycontroldialog.h"
#include<QStandardItemModel>
#include <mainbussniessview.h>
#include <myhelper.h>
#include <QtSql/QSqlTableModel>
#include <QtSql/QSqlQuery>

QualityControlDialog::QualityControlDialog(QWidget *parent, MainBussniessView* pMainView) :
    QTabWidget(parent),pMainBussninessView(pMainView),
    ui(new Ui::QualityControlDialog)
{
    nRow = 0;
    ui->setupUi(this);
    this->setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
    QPoint point(0, 0);
    this->move(point);

    //subItemTableModel = new QSqlTableModel(this);

    ui->dt_QcDate->setDateTime(QDateTime::currentDateTime());
    subItemTableModel = NULL;
    /*pStandardItemModel = NULL;
    pStandardItem = NULL;
    if(pStandardItemModel == NULL){
        pStandardItemModel = new QStandardItemModel();
    }*/
    //QList<ItemModel> lstItemModel;
    //nCount = pMainBussninessView->GetItemList(lstItemModel);
    //for(int i = 0;i < nCount;i++){
        //pStandardItem = new QStandardItem();
        //pStandardItem->setCheckable(true);
        //pStandardItem->setText(lstItemModel[i].getItemName());
        //pStandardItem->setCheckState(Qt::Checked);
        //pStandardItemModel->setItem(i, pStandardItem);

        ///connect(pStandardItemModel, SIGNAL(itemChanged(QStandardItem *item)), this, SLOT(on_SelectItem(QStandardItem*)));
    //}
    itemTableModel = new QSqlTableModel();
    pMainView->GetItemName(itemTableModel);
    ui->ItemListView->setModel(itemTableModel);
    connect(pMainBussninessView, SIGNAL(Qc_SubItemResult(QSqlTableModel*)), this, SLOT(on_btnQc_SubItemResult(QSqlTableModel*)));
    LanguageMananger();
    InstallDefaultLanguage();
    QRegExp regx("[0-9]+$");
    validator = new QRegExpValidator(regx, this);
    ui->edt_BatchNo->setValidator( validator );
    //ui->edt_CvValue->setValidator(validator);
    ui->edt_QcValue->setValidator(validator);
    ui->edt_TargetValue->setValidator(validator);

}

void QualityControlDialog::LanguageMananger(){
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
void QualityControlDialog::InstallDefaultLanguage(){

    qApp->removeTranslator(&App::translator);
    if(App::current_language == (int)QLocale::Chinese){
        App::translator.load(App::language_Chinese);
    }else {
        App::translator.load(App::language_English);
    }
    qApp->installTranslator(&App::translator);
    ui->retranslateUi(this);
}

QualityControlDialog::~QualityControlDialog()
{
    if(validator != NULL){
        delete validator;
    }
    if(itemTableModel != NULL){
        delete itemTableModel;
    }
    if(subItemTableModel != NULL){
        delete subItemTableModel;
    }
    /*for(int i = 0; i < nCount; i++){
        delete pStandardItemModel->item(i);
    }
    delete pStandardItemModel;
    */
    delete ui;
}

void QualityControlDialog::on_btn_QC_Saves_clicked()
{
    QC_SubItemModel subItemModel;
    subItemModel.setQc_Value(ui->edt_QcValue->text());
    int itemNo = pMainBussninessView->GetItemNoByItemName(itemName);
    subItemModel.setItemNo(itemNo);
    subItemModel.setQc_Date(ui->dt_QcDate->dateTime().currentDateTime().toString("yyyy-MM-dd"));
    pMainBussninessView->QualityControlItemSave(subItemModel);
}
void QualityControlDialog::on_btnQc_SubItemResult(QSqlTableModel* subItemModel){
    ui->tb_SubItemView->setModel(subItemModel);
    ui->tb_SubItemView->setEditTriggers(QAbstractItemView::NoEditTriggers);   //使其不可编辑
    ui->tb_SubItemView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tb_SubItemView->setSelectionBehavior(QAbstractItemView::SelectRows);
    //ui->tbview_TestResult->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    ui->tb_SubItemView->verticalHeader()->hide();
}

void QualityControlDialog::on_ItemListView_pressed(const QModelIndex &index)
{
    int row=index.row();
     /*if(row >= 0)
     {*/
    itemName = index.data(Qt::DisplayRole).toString();
    if(subItemTableModel == NULL){
        subItemTableModel = new QSqlTableModel();
    }
    //itemName =pStandardItemModel->data(index,Qt::DisplayRole).toString();
     /*myHelper::ShowMessageBoxInfo(itemName);
     }
     else
     {
        myHelper::ShowMessageBoxInfo(tr("please select a item"));
     }*/
    itemNo = pMainBussninessView->GetItemNoByItemName(itemName);
    pMainBussninessView->Qc_Query(itemNo, subItemTableModel);
    QSqlQuery query = subItemTableModel->query();
    lstQcValue.clear();
    query.first();
    do {
        QC_SubItemModel subItemModel;
        //subItemModel.setItemNo(query.value(0).toInt());
        subItemModel.setQc_Value(query.value(1).toString());
        //subItemModel.setQc_Date(query.value(2).toString());
        lstQcValue.append(subItemModel.getQc_Value().toFloat());
    }while (query.next());
    ui->tb_SubItemView->setModel(subItemTableModel);
    ui->tb_SubItemView->setEditTriggers(QAbstractItemView::NoEditTriggers);   //使其不可编辑
    ui->tb_SubItemView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tb_SubItemView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tb_SubItemView->verticalHeader()->hide();

}

void QualityControlDialog::on_btn_Calculate_clicked()
{
    float cvValue = 0.0f;
    QualityControlModel qcModel;
    qcModel.setBatchNo(ui->edt_BatchNo->text());
    qcModel.setItemNo(itemNo);
    qcModel.setTargetValue(ui->edt_TargetValue->text().toFloat());
    qcModel.plstQcModel = lstQcValue;
    pMainBussninessView->Qc_MainItemSave(qcModel, cvValue);
    ui->edt_CvValue->setText(QString("%1").arg(cvValue));
    //double cv = pMainBussninessView->CalculateCV();
}
