#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include<qtimer.h>
#include <QMainWindow>
#include <mainbuttondialog.h>
#include <QTranslator>
namespace Ui {
class MainWindow;
}

enum MAIN_BUTTON{
    TESTING = 0,
    HISTORY = 1,
    QUALITY = 2,
    CALIBRATE = 3,
    ITEM = 4,
    SYSTEM = 5,
    DEBUG = 6,
    MAIN_BTN = 7
};

class TestingDialog;
class queryDialog;
class QualityControlDialog;
class ParameterDialog;
class CalibrateDialog;
class SystemDialog;
class MaintenanceDialog;
class MainBussniessView;
class SyszuxPinyin;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void LanguageMananger();
    void InstallDefaultLanguage();
protected:
    bool eventFilter(QObject *obj, QEvent *event);
    void mouseMoveEvent(QMouseEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *);
private slots:
    void on_btn_Close_clicked();
    void TestingActionSlot();
    void HistoryActionSlot();
    void QualityActionSlot();
    void CalibrateActionSlot();
    void ItemActionSlot();
    void SystemActionSlot();
    void DebugActionSlot();
    void MainActionSolt();

    void onSystemTime();
    void on_btn_Zh_En_clicked();

private:
    Ui::MainWindow *ui;
    MainButtonDialog* m_MainButtonDlg;
    MAIN_BUTTON buttonState;
    QPoint mousePoint;
    bool mousePressed;
    bool max;
    QRect location;
    //QTranslator* translator;
    QAction *testingAction;
    QAction *qualityAction;
    QAction *systemAction;
    QAction *calibrateAction;
    QAction *historyAction;
    QAction *settingAction;
    QAction *itemAction;
    QAction *debugAction;
    QAction *mainAction;
    QMenu *menu;                //菜单

    void createAction();        //创建动作
    void createMenu();          //创建菜单
    void createContentMenu();   //创建上下文菜单

    void on_btn_Max_clicked();
    void hideButton(MAIN_BUTTON button);
    void selectButton(MAIN_BUTTON button);
    void InitStyle();

    TestingDialog *m_TestDialog;
    queryDialog *m_queryDialog;
    QualityControlDialog *m_qualityControlDialog;
    ParameterDialog *m_ParameterDialog;
    CalibrateDialog *m_calibrateDialog;
    SystemDialog *m_systemDialog;
    MaintenanceDialog* m_MaintenanceDialog;
    QTimer *timer;

    MainBussniessView* m_MainView;
};

#endif // MAINWINDOW_H
