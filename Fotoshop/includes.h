/*! \header General header \brief includes most of the global librarys and variables that are called in every function */

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
#include <QPoint>
#include <vector>


#define TRUE 1
#define FALSE 0
extern int opened; /*! \var int opened \brief variable to keep track of opening an image */
extern QString filename; /*! \var QString filename \brief stores the datapath of the image the user selects to open */
extern int screenheight;/*! \var int screenheight \brief stores the pixel height of the monitor running the program */
extern int screenwidth;/*! \var screenwidth \brief stores pixel width of the monitor running the program */
extern QImage loadedImage; /*! \var QImage loadedImage \brief stores the image into memory after the datapath has been selected */
extern QImage scaledImage;/*! \var QImage scaledImage \brief keeps track of the scaled images for resizing */
extern double picsize; /*! \var double picsize \brief size factor for zooms */
extern int currentImageNumber; /*! \var iterator to keep track of the Undo stack */
extern int isblank;/*! \var int isblank \brief 1 or 0 value to see if the image is blank or loaded*/
extern bool pen; /*! \var bool pen \brief keeps track of whether the pen is down or up */
extern bool eraser;/*! \var bool eraser \brief keeps track of whether the eraser is down or up */
extern bool brush;/*! \var bool brush \brief keeps track of whether the brush is down or up */
extern bool text;/*! \var bool text \brief keeps track of whether the text tool is down or up */
extern bool drawing;/*! \var bool drawing \brief keeps track of whether the pen is currently drawing */
extern QPoint pointxy; /*! \var QPoint pointxy \brief keeps track of the pixel coordinates of mouse clicks */
extern QPoint pointxy2;
extern QPen thePen; /*! \var QPen thePen \brief keeps track of pen used and its properties such as width, color, etc. */

/*! Undo Class */
class undoArr
{

public:
    QImage currImg; /*! \var QImage currImg \brief the image pushed onto the stack */
    bool hasPic; /*! \var bool hasPic \brief a variable to keep track of whether a stack position is empty */
    void push(QImage file); /*! \fn void push(QImage file) \brief pushes the image onto the stack */
    void pop();/*! \fn void pop() \brief pops the image from the stack */
    int size; /*! \var int size \brief keeps track of the size of the undo stack */
};


#endif // INCLUDES_H
