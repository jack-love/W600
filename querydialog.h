#ifndef QUERYDIALOG_H
#define QUERYDIALOG_H

#include <QTabWidget>
#include <QModelIndex>

namespace Ui {
class queryDialog;
}
class MainBussniessView;
class QSqlTableModel;
class QSqlQueryModel;
class queryDialog : public QTabWidget
{
    Q_OBJECT

public:
    explicit queryDialog(QWidget *parent = 0, MainBussniessView*pMainBussniessView = NULL);
    ~queryDialog();

private slots:
    void on_btn_query_date_clicked();
    void on_PatientResult(QSqlTableModel*);
    void on_QuerySampleResult(QSqlTableModel*);

    void on_SampleResult(QSqlTableModel*);
    void on_tablevew_Patient_pressed(const QModelIndex &index);

    void on_btn_ItemQuery_clicked();

private:
    Ui::queryDialog *ui;
    MainBussniessView * pMainView;
    int nRow;
    QSqlTableModel* patientModel;
    QSqlQueryModel* itemTableModel;
    void LanguageMananger();
    void InstallDefaultLanguage();
};

#endif // QUERYDIALOG_H
