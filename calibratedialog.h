#ifndef CALIBRATEDIALOG_H
#define CALIBRATEDIALOG_H

#include <QTabWidget>
#include <QModelIndex>
#include <calibrateobservermodel.h>

namespace Ui {
class CalibrateDialog;
}
class MainBussniessView;
class QSqlQueryModel;
class QSqlTableModel;
class QValidator;
class QTableView;
class CalibrateDialog : public QTabWidget
{
    Q_OBJECT

public:
    explicit CalibrateDialog(QWidget *parent = 0, MainBussniessView* pMainView = NULL);
    ~CalibrateDialog();

private slots:
    void on_lstView_ItemName_pressed(const QModelIndex &index);

    void on_btn_CalibrateSave_clicked();

    void on_btn_OberserveQuery_clicked();

    void on_CalibrateObserverveResult(QSqlTableModel*calibrateTableModel);
    void on_btn_CalibrateData_clicked();

    void on_btn_CalibrateStop_clicked();

    void on_btn_NextPage_clicked();

    void on_btn_FirstPag_clicked();

    void on_btn_PreviousPage_clicked();

    void on_btn_LastPage_clicked();

private:
    Ui::CalibrateDialog *ui;
    MainBussniessView *pMainBussView;
    QSqlQueryModel *pQueryModel;
    QString strItemName;
    QSqlQueryModel *pTableModel;

    void LanguageMananger();
    void InstallDefaultLanguage();
    QValidator *validator;
    bool bEnableButton;
    bool pageHome(QTableView *p);
    bool pageDown(QTableView *p,bool isLoop);
    bool pageEnd(QTableView *p);
    int pageCount(QTableView *p);
    bool pageTo(QTableView *p, int pageNO);
    bool pageUp(QTableView *p,bool isLoop);

};

#endif // CALIBRATEDIALOG_H
