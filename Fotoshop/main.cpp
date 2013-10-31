#include "mainwindow.h"
#include "workingwindow.h"

int opened = 0;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
