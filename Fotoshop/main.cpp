#include "mainwindow.h"
#include "workingwindow.h"

int opened = 0;
QString filename;
int screenheight;
int screenwidth;
QImage loadedImage;
QImage scaledImage;
double picsize;
int currentImageNumber = 0;
int isblank;
bool pen = FALSE;
bool drawing = FALSE;
bool eraser = FALSE;
bool brush = FALSE;
bool text = FALSE;
undoArr *undofunc;
QPoint pointxy;
QPoint pointxy2;
//QPixmap buffer;


int main(int argc, char *argv[])
{

    picsize = 1;
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}

