#include "mainwindow.h"
#include "workingwindow.h"

int opened = 0;
QString filename;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
