#include "systemdialog.h"
#include "ui_systemdialog.h"
#include <mainbussniessview.h>
#include <App.h>
SystemDialog::SystemDialog(QWidget *parent, MainBussniessView *pMainBussniessView) :
    QTabWidget(parent),pMainView(pMainBussniessView),
    ui(new Ui::SystemDialog)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
    QPoint point(0, 0);
    this->move(point);
    LanguageMananger();
    InstallDefaultLanguage();
}
void SystemDialog::LanguageMananger(){
    //translator = NULL;
    //QString lanStr = OptionManager::getInstance()->getRegConfig(OPTION_LAN_STR);

    if(0 == App::lanStr.compare("CHINESE", Qt::CaseInsensitive)){
        App::current_language = QLocale::Chinese;
    }else if(0 == App::lanStr.compare("ENGLISH", Qt::CaseInsensitive)){
        App::current_language = QLocale::English;
    }else{
        App::current_language = QLocale::system().language();
    }

}
void SystemDialog::InstallDefaultLanguage(){

    qApp->removeTranslator(&App::translator);
    if(App::current_language == (int)QLocale::Chinese){
        App::translator.load(App::language_Chinese);
    }else {
        App::translator.load(App::language_English);
    }
    qApp->installTranslator(&App::translator);
    ui->retranslateUi(this);
}
SystemDialog::~SystemDialog()
{
    delete ui;
}

void SystemDialog::on_ck_print_pressed()
{
    ui->ck_print->setChecked(SystemConfig::isPrint);
}
