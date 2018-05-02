#ifndef TESTINGDIALOG_H
#define TESTINGDIALOG_H

#include <QDialog>
#include <QItemSelection>
#include <patientmodel.h>
#include <App.h>
#include <serialportctrl.h>
namespace Ui {
class TestingDialog;
}
class MainBussniessView;
class QSqlTableModel;
class QValidator;
class TestingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TestingDialog(QWidget *parent = 0, MainBussniessView* pMainBussniessView = NULL);

    ~TestingDialog();
signals:
  //  void testStart();
   // void testStop();
private slots:
    void on_btn_Start_clicked();

    void on_btn_Stop_clicked();

    bool on_TestResult(QSqlTableModel*);

    bool on_PositionStatus(uint );

    void on_btn_testSave_clicked();

    void on_btn_testDelete_clicked();

    //void on_selectResult(QItemSelection,QItemSelection);
    void on_tbview_TestResult_pressed(const QModelIndex &index);

    void on_edt_SampleNo_returnPressed();

    void on_patientInfo(PatientModel);


    void on_btn_Reset_clicked();

    void on_btn_testPrint_clicked();

private:
    Ui::TestingDialog *ui;
    MainBussniessView *pMainView;
    REPORT report;
    int nRow;
    void createDatabase();
    void showData();
    void LanguageMananger();
    void InstallDefaultLanguage();
    int m_SampleNo;
    char PrintData[16][32];
    QValidator *validator;
    SerialPortCtrl serialPort;
    bool bSerialPort;
};

#endif // TESTINGDIALOG_H
