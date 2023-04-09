#include "mainwindow.h"
#include <QString>
#include <QDebug>
#include <QApplication>

#include "../../src/mem/cache.cpp"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    qInfo("hello");
    return a.exec();
}
