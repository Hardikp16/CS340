#include "mainwindow.h"
#include "workingwindow.h"

int opened = 0;
QString filename;
int screenheight;
int screenwidth;
QImage loadedImage;
QImage scaledImage;
double picsize;

int main(int argc, char *argv[])
{
    picsize = 1;
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
