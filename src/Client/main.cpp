#include "mainwindow.h"
#include "settingswindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    w.Init();
    return a.exec();
}
