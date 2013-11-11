#ifndef INCLUDES_H
#define INCLUDES_H

#include <QFileDialog>
#include <stdlib.h>
#include <QMainWindow>
#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QFileDialog>
#include <stdio.h>
#include <iostream>
#include <QMessageBox>
#include <QLabel>
#include <string>
#include <QImage>
#include <QPixmap>
#include <QDesktopWidget>
#include <QStyle>
#include <Qt>
#include <QtMath>
#include <QEvent>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QPen>
#include <QBrush>
#include <QColor>


#define TRUE 1
#define FALSE 0
extern int opened;
extern QString filename;
extern int screenheight;
extern int screenwidth;
extern QImage loadedImage;
extern QImage scaledImage;
extern double picsize;
extern int currentImageNumber;
extern int isblank;

class undoArr
{

public:
    QImage currImg;
    bool hasPic;
    void push(QImage file);
    void pop();

};


#endif // INCLUDES_H
