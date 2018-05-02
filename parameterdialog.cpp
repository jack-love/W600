#include "parameterdialog.h"
#include "ui_parameterdialog.h"
#include <mainbussniessview.h>
#include <QtSql/QSqlTableModel>
#include <itemparametermodel.h>
ParameterDialog::ParameterDialog(QWidget *parent, MainBussniessView * pMainView) :
    QTabWidget(parent), pMainBussView(pMainView),
    ui(new Ui::ParameterDialog)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
    QPoint point(0, 0);
    this->move(point);
    connect(pMainView, SIGNAL(Item_Result(QSqlTableModel*)), this, SLOT(on_Item_Result(QSqlTableModel*)));
    connect(pMainView, SIGNAL(ItemParameter_Result(QSqlTableModel*)), this, SLOT(on_ItemParameter(QSqlTableModel*)));
    connect(pMainView, SIGNAL(SampleType_Result(QSqlTableModel*)), this, SLOT(on_SampleType_Result(QSqlTableModel*)));
    pTableModel = new QSqlQueryModel(this);
    pMainBussView->GetItemName(pTableModel);
    ui->cbb_ItemName->setModel(pTableModel);

    sampleTypeModel = NULL;
    itemModel = NULL;
    itemParamModel = NULL;

    SetSampleType();
    SetItem();
    SetItemParameter();

    LanguageMananger();
    InstallDefaultLanguage();
    QRegExp regx("[0-9]+$");
    validator = new QRegExpValidator(regx, this);
    ui->edt_ItemNo->setValidator(validator);
    ui->edt_RefMin->setValidator(validator);
    ui->edt_RefMax->setValidator(validator);
    ui->edtPostSequance->setValidator(validator);

}

void ParameterDialog::SetSampleType(){
    if(sampleTypeModel == NULL){
        sampleTypeModel = new QSqlTableModel();
    }
    pMainBussView->SampleType_Query(sampleTypeModel);
    sampleTypeModel->setHeaderData(0,Qt::Horizontal,tr("样本类型号"));
    sampleTypeModel->setHeaderData(1,Qt::Horizontal,tr("样本类型名"));
    sampleTypeModel->setHeaderData(2,Qt::Horizontal,tr("简称"));
    ui->tbView_SampleType->setModel(sampleTypeModel);
}
void ParameterDialog::SetItem(){
    if(itemModel == NULL){
        itemModel = new QSqlTableModel();
    }
    pMainBussView->Item_Query(itemModel);
    itemModel->setHeaderData(0,Qt::Horizontal,tr("项目号"));
    itemModel->setHeaderData(1,Qt::Horizontal,tr("项目名"));
    itemModel->setHeaderData(2,Qt::Horizontal,tr("简称"));
    ui->tbView_Parameter->setModel(itemModel);
}
void ParameterDialog::SetItemParameter(){
    if(itemParamModel == NULL){
        itemParamModel = new QSqlTableModel();
    }
    pMainBussView->ItemParameter_Query(itemParamModel);
    itemParamModel->setHeaderData(0,Qt::Horizontal,tr("项目号码"));
    itemParamModel->setHeaderData(1,Qt::Horizontal,tr("项目名称"));
    itemParamModel->setHeaderData(2,Qt::Horizontal,tr("项目性质"));
    itemParamModel->setHeaderData(3,Qt::Horizontal,tr("参考最小值"));
    itemParamModel->setHeaderData(4,Qt::Horizontal,tr("参考最大值"));
    itemParamModel->setHeaderData(5,Qt::Horizontal,tr("单位"));
    ui->tbView_ItemResult->setModel(itemParamModel);
}

void ParameterDialog::LanguageMananger(){
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
void ParameterDialog::InstallDefaultLanguage(){

    qApp->removeTranslator(&App::translator);
    if(App::current_language == (int)QLocale::Chinese){
        App::translator.load(App::language_Chinese);
    }else {
        App::translator.load(App::language_English);
    }
    qApp->installTranslator(&App::translator);
    ui->retranslateUi(this);
}

ParameterDialog::~ParameterDialog()
{
    if(validator != NULL){
        delete validator;
    }
    if(pTableModel != NULL){
        delete pTableModel;
    }
    if(sampleTypeModel != NULL){
        delete sampleTypeModel;
    }
    if(itemModel != NULL){
        delete itemModel;
    }
    if(itemParamModel != NULL){
        delete itemParamModel;
    }
    delete ui;
}

void ParameterDialog::on_btn_ItemSave_clicked()
{
    ItemModel itemModel;
    itemModel.setItemNo(ui->edt_ItemNo->text().toInt());
    itemModel.setItemName(ui->edt_ItemName->text());
    itemModel.setFlag(ui->edt_Flag->text());
    pMainBussView->Item_Save(itemModel);
    SetItem();
    return;
}
void ParameterDialog::on_Item_Result(QSqlTableModel* tableModel){
    ui->tbView_Parameter->setModel(tableModel);
    ui->tbView_Parameter->setEditTriggers(QAbstractItemView::NoEditTriggers);   //使其不可编辑
    ui->tbView_Parameter->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tbView_Parameter->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tbView_Parameter->verticalHeader()->hide();
    return;
}

void ParameterDialog::on_btn_ItemSave_2_clicked()
{
    ItemParameterModel paramModel;
    paramModel.setItemName(ui->cbb_ItemName->currentText());
    paramModel.setItemNo(pMainBussView->GetItemNoByItemName(paramModel.getItemName()));
    paramModel.setItemProperty(ui->edt_Property->text());
    paramModel.setRefMin(ui->edt_RefMin->text().toFloat());
    paramModel.setRefMax(ui->edt_RefMax->text().toFloat());
    paramModel.setUnit(ui->edt_Unit->text());
    paramModel.setCheckWay(ui->edt_CheckWay->text());
    paramModel.setPostSequence(ui->edtPostSequance->text().toInt());
    pMainBussView->ItemParameter_Save(paramModel);
    SetItemParameter();
}
void ParameterDialog::on_ItemParameter(QSqlTableModel*itemParamModel){
    ui->tbView_ItemResult->setModel(itemParamModel);
    ui->tbView_ItemResult->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tbView_ItemResult->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tbView_ItemResult->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tbView_ItemResult->verticalHeader()->hide();
}

void ParameterDialog::on_btn_SampleTypeSave_clicked()
{
    SampleTypeModel sampleTypeModel;
    sampleTypeModel.setSampleTypeNo(ui->edt_SampleTypeNo->text().toInt());
    sampleTypeModel.setSampleTypeName(ui->edt_SampleTypeName->text());
    sampleTypeModel.setSampleFlag(ui->edt_Flag_2->text());
    pMainBussView->SampleTytpeSave(sampleTypeModel);
    SetSampleType();

}

void ParameterDialog::on_SampleType_Result(QSqlTableModel*sampleTypeModel){
    ui->tbView_SampleType->setModel(sampleTypeModel);
    ui->tbView_SampleType->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tbView_SampleType->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tbView_SampleType->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tbView_SampleType->verticalHeader()->hide();
}
