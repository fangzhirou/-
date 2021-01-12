#include "mainwindow.h"
#include"dialog.h"
#include"ui_dialog.h"
#include"ui_mainwindow1.h"
#include <QApplication>
#include<QDialog>



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Dialog my1;//创建一个指向子窗口的对象
    MainWindow w;
    QObject::connect(&my1, SIGNAL(nextpage();),
                      &w,SLOT(shownextpage()));
    w.show();
    my1.show();
    return a.exec();





}

