#include "mainwindow.h"
#include "mywidget.h"
#include <QApplication>
#include <QPushButton>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w, w2;
    w.show();
    //w2.show();

    //MyWidget w;
    //w.show();

    return a.exec();
}
