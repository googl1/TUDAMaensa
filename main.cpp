#include <QtGui/QApplication>
#include <QTextCodec>
#include <QMenuBar>

#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));

    QApplication a(argc, argv);
    MainWindow w;
#if defined(Q_WS_S60)
    w.showMaximized();
//    QMenuBar *menu = new QMenuBar();
//    menu->addMenu("setup");
//    menu->addAction();
//    w.setMenuBar(menu);
#else
    w.show();
    w.work();
#endif



    return a.exec();
}
