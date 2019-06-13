#include "mainwindow.h"
#include <QApplication>
#include "myfilter.h"
#include <vector>
#include <array>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
