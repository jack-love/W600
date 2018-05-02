#ifndef QUALITYCONTROLDIALOG_H
#define QUALITYCONTROLDIALOG_H

#include <QTabWidget>
#include<QModelIndex>
//#include <itemmodel.h>
namespace Ui {
class QualityControlDialog;
}
class MainBussniessView;
class QStandardItem;
class QStandardItemModel;
class QSqlTableModel;
class QValidator;
class QualityControlDialog : public QTabWidget
{
    Q_OBJECT

public:
    explicit QualityControlDialog(QWidget *parent = 0, MainBussniessView* pMainView = NULL);
    ~QualityControlDialog();

private slots:
    void on_btn_QC_Saves_clicked();
    void on_ItemListView_pressed(const QModelIndex &index);
    void on_btnQc_SubItemResult(QSqlTableModel*);
    void on_btn_Calculate_clicked();

private:
    Ui::QualityControlDialog *ui;
    MainBussniessView *pMainBussninessView;
    //int nCount;
    //QStandardItem *pStandardItem;
    //QStandardItemModel *pStandardItemModel;
    QSqlTableModel *itemTableModel;
    QSqlTableModel *subItemTableModel;
    int nRow;
    QString itemName;
    int itemNo;
    QList<double> lstQcValue;
    void LanguageMananger();
    void InstallDefaultLanguage();
    QValidator *validator;
};

#endif // QUALITYCONTROLDIALOG_H
