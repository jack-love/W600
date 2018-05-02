#include "mainwindow.h"
#include <QApplication>
#include "myhelper.h"
#include <frminput.h>
#include <App.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    /*QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));       //支持Tr中文
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));//支持中文文件名显示
    */

    myHelper::SetUTF8Code();
    QFont font;
    font.setPointSize(11);//实际上是16的字号，但设成16却不行
    font.setFamily(("WenQuanYi Zen Hei"));
    font.setBold(true);
    a.setFont(font);
    myHelper::SetStyle("black");//黑色风格
    //myHelper::SetStyle("blue");//蓝色风格
    //myHelper::SetStyle("gray");//灰色风格
    //myHelper::SetStyle("navy");//天蓝色风格
    myHelper::SetChinese();
    frmInput::Instance()->hide();

    MainWindow w;
    w.LanguageMananger();
    w.InstallDefaultLanguage();
    //w.setWindowFlags(w.windowFlags() &~Qt::WindowMaximized);
    //w.setWindowFlags(Qt::CustomizeWindowHint);
    w.setWindowFlags(Qt::FramelessWindowHint);//去掉标题栏
    //w.setWindowFlags(Qt::WindowStaysOnTopHint);
    w.show();

    return a.exec();
}
