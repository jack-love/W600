#include "maintenancedialog.h"
#include "ui_maintenancedialog.h"

MaintenanceDialog::MaintenanceDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MaintenanceDialog)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
    QPoint point(0, 0);
    this->move(point);
}

MaintenanceDialog::~MaintenanceDialog()
{
    delete ui;
}
