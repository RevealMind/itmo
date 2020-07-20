#include "mainwindow.h"

#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    //IndexerProgressDialog w(nullptr);
    //w.show();

    return a.exec();
}
