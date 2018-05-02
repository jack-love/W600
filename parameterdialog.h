#ifndef PARAMETERDIALOG_H
#define PARAMETERDIALOG_H

#include <QTabWidget>

namespace Ui {
class ParameterDialog;
}
class MainBussniessView;
class QSqlTableModel;
class QSqlQueryModel;
class QValidator;
class ParameterDialog : public QTabWidget
{
    Q_OBJECT

public:
    explicit ParameterDialog(QWidget *parent = 0, MainBussniessView* pMainView = NULL);
    ~ParameterDialog();

private slots:
    void on_btn_ItemSave_clicked();
    void on_Item_Result(QSqlTableModel* tableModel);
    void on_btn_ItemSave_2_clicked();
    void on_ItemParameter(QSqlTableModel*itemParamModel);
    void on_btn_SampleTypeSave_clicked();
    void on_SampleType_Result(QSqlTableModel*sampleTypeModel);
private:
    Ui::ParameterDialog *ui;
    MainBussniessView * pMainBussView;
    QSqlQueryModel *pTableModel;
    QSqlQueryModel *itemModel;
    QSqlTableModel* sampleTypeModel;
    QSqlTableModel* itemParamModel;
    void LanguageMananger();
    void InstallDefaultLanguage();
    QValidator *validator;

    void SetSampleType();
    void SetItem();
    void SetItemParameter();
};

#endif // PARAMETERDIALOG_H
