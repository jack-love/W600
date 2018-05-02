#ifndef QPROGRESSDIALOG_H
#define QPROGRESSDIALOG_H

#include <QDialog>
namespace Ui {
class QProgressDialog;
}

class QProgressDialog : public QDialog
{
    Q_OBJECT

public:
    explicit QProgressDialog(QWidget *parent = 0, int nMix = 0, int nMax = 100);
    ~QProgressDialog();
    void SetValue(int i);
private:
    Ui::QProgressDialog *ui;
};

#endif // QPROGRESSDIALOG_H
