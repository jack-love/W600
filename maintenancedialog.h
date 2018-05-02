#ifndef MAINTENANCEDIALOG_H
#define MAINTENANCEDIALOG_H

#include <QDialog>

namespace Ui {
class MaintenanceDialog;
}

class MaintenanceDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MaintenanceDialog(QWidget *parent = 0);
    ~MaintenanceDialog();

private:
    Ui::MaintenanceDialog *ui;
};

#endif // MAINTENANCEDIALOG_H
