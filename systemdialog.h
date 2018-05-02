#ifndef SYSTEMDIALOG_H
#define SYSTEMDIALOG_H

#include <QTabWidget>

namespace Ui {
class SystemDialog;
}
class MainBussniessView;
class SystemDialog : public QTabWidget
{
    Q_OBJECT

public:
    explicit SystemDialog(QWidget *parent = 0, MainBussniessView *pMainBussniessView = NULL);
    ~SystemDialog();

private slots:
    void on_ck_print_pressed();

private:
    Ui::SystemDialog *ui;
    MainBussniessView *pMainView;
    void LanguageMananger();
    void InstallDefaultLanguage();
};

#endif // SYSTEMDIALOG_H
