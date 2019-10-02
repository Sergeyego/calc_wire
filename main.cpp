#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    //QTextCodec *codec = QTextCodec::codecForName("Utf8");
    //QTextCodec::setCodecForTr(codec);
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
