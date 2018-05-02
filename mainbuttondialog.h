#ifndef MAINBUTTONDIALOG_H
#define MAINBUTTONDIALOG_H

#include <QDialog>

namespace Ui {
class MainButtonDialog;
}

class MainButtonDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit MainButtonDialog(QWidget *parent = 0);
    ~MainButtonDialog();
signals:
    void on_btnTesting();

    void on_btn_Quality();

    void on_btn_Calibrate();

    void on_btn_history();

    void on_btn_ItemParam();

    void on_btn_System();

    void on_btn_Debug();
private slots:
    void on_btnTesting_clicked();

    void on_btn_history_clicked();

    void on_btn_QualityControl_clicked();

    void on_btn_Calibration_clicked();

    void on_btn_ItemParameter_clicked();

    void on_btn_System_clicked();

    void on_btn_Maintancance_clicked();

private:
    Ui::MainButtonDialog *ui;
};

#endif // MAINBUTTONDIALOG_H
