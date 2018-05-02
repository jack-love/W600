#include "mainbuttondialog.h"
#include "ui_mainbuttondialog.h"

MainButtonDialog::MainButtonDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainButtonDialog)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
    QPoint point(0, 0);
    this->move(point);
}

MainButtonDialog::~MainButtonDialog()
{
    delete ui;
}

void MainButtonDialog::on_btnTesting_clicked()
{
    emit on_btnTesting();
}

void MainButtonDialog::on_btn_history_clicked()
{
    emit on_btn_history();
}

void MainButtonDialog::on_btn_QualityControl_clicked()
{
    emit on_btn_Quality();
}

void MainButtonDialog::on_btn_Calibration_clicked()
{
    emit on_btn_Calibrate();
}

void MainButtonDialog::on_btn_ItemParameter_clicked()
{
    emit on_btn_ItemParam();
}

void MainButtonDialog::on_btn_System_clicked()
{
    emit on_btn_System();
}

void MainButtonDialog::on_btn_Maintancance_clicked()
{
    emit on_btn_Debug();
}
