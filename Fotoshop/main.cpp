/*!
 ************************************************************************************
 ************************************************************************************
 **                                   FOTOSHOP                                     **
 ************************************************************************************
 ************************************************************************************
 ***A lite but powerful painting and editing software written in C++ with Qt Creator
 ***This program is targeted towards home users looking to upgrade from paint but
 ***unwilling to invest in something like lightroom or photoshop
 ***
 ***
 ***AUTHOR : LEDIO SINJARI
 ***
 ***WRITTEN FOR CS 340 - FALL 2013
 ***INSTRUCTOR LUC RENAMBOT
 *
 *
 *
 *
 * \file Main.cpp \brief main Cpp file for program
*/

#include "mainwindow.h"
#include "workingwindow.h"

int opened = 0; //! \var opened \brief keeps track of whether an image is opened
QString filename; //! \var filename \brief string that stores the directory location of the desired file
int screenheight; //! \var screenheight \brief stores the height of the montor currently being used;
int screenwidth; //! \var screenwidth \brief stores the width of the monitor currently being used;
QImage loadedImage; //! \var loadedImage \brief stores the image from the loaded directory
QImage scaledImage;//! \var scaledImage \brief dimension data to scale the image
double picsize; //! \var picsize \brief scale factor for zooming in and out
int currentImageNumber = 0; //! \var currentImageNumber \brief starting position of the undo stack
int isblank; //! \var isblank \brief keep track of whether the user opted to load an image or start a new file
bool pen = FALSE; //! \var pen \brief keep track of whether the pen tool was selected
bool drawing = FALSE; //! \var drawing \brief keep track of whether the pen is down on the label
bool eraser = FALSE; //! \var eraser \brief keep track of whether the eraser is selected
bool brush = FALSE; //! \var brush \brief keep track of whether the brush tool is selected
bool text = FALSE;
undoArr *undofunc; //! \var undofunc \brief initialize the data structure that stores previous moves
QPoint pointxy; //! \var pointxy \brief keep track of the position of the mouse
QPoint pointxy2;
QPen thePen; //! \var thePen \brief keep track of the properties of the current pen

double myInputSize; //! \var myInputSize \brief hold the values to resize images

std::vector<QImage> undoVector;
//QPixmap buffer;



int main(int argc, char *argv[]) //! \fn main \par argc \par argv[]
{


    picsize = 1; //! init pic size to 1, scale factor is currently 1
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec(); //! \return run the UI
}

