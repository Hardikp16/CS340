/*! \file workingWindow \brief main code to run the workinng UI*/

#include "workingwindow.h"
#include "ui_workingwindow.h"
#include "filters.h"
#include "darkroom.h"

workingwindow::workingwindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::workingwindow)
{
    ui->setupUi(this);
    ui->imageLabel->installEventFilter(this);
    undofunc = new undoArr[256];

    bucket = FALSE;

    /*! creating a proxy to edit with */
    if (isblank == 1)
        {
        QImage image(1600, 900, QImage::Format_RGB32); //! create a blank white image at 1600 x 900
            image.fill(Qt::white); //! fill it in blank white
            loadedImage = image;
        }
    else
    {
        QImage image(filename);
        loadedImage = image;
    }
    QImage temp2(270, 115, QImage::Format_RGB32); //! set a blank Qlabel for ui design
    temp2.fill(Qt::black); //! fill the blank label with black
    colorPreview = temp2;
    ui->COLORPREVIEW->setPixmap(QPixmap::fromImage(colorPreview));


    colorFactor = 2.55; //! set a multiplier so sliders represent color values

    ui->horizontalSlider->setValue(25);

    ui->CropFromDown->setValue(0); //! set horizontal slider position
    ui->CropFromTop->setValue(100); //! set second horizontal slider position
    ui->CropFromLeft->setValue(0); //! set first vertical slider position
    ui->CropFromRight->setValue(100); //! set second vertical slider position

    topLinePos = 0;
    bottomLinePos = loadedImage.height() -1;
    rightLinePos = loadedImage.width() -1;
    leftLinePos = 0;

    QImage temp(":/Icon/color_wheel1.png");  //! set an image as a color wheel for reference
    ColorWheel = temp;
    ColorWheel = ColorWheel.scaled(screenwidth / 4, screenheight / 4, Qt::KeepAspectRatio, Qt::FastTransformation); //! scale the color wheel to fit the window

    ui->colorWheel->setPixmap(QPixmap::fromImage(ColorWheel));
    ui->imageLabel->setPixmap(QPixmap::fromImage(loadedImage));
    ui->imageLabel->adjustSize();

    undofunc[0].push(loadedImage); //! push the initial picture to the base of the stack
    undoVector.push_back(loadedImage);

    thePen.setJoinStyle(Qt::RoundJoin); //! smooth out pen lines
    thePen.setCapStyle(Qt::RoundCap); //! round out the pen cap

    ui->imageLabel->isMinimized();
}

workingwindow::~workingwindow()
{
    delete ui;
}


void workingwindow::on_quitButton_clicked()
{
    delete [] undofunc;
    exit (EXIT_SUCCESS);
}

void workingwindow::on_greyScale_clicked() //! greyscale button clicked
{
    loadedImage = greyscale(loadedImage); //! set greyscale on loaded image

    ui->imageLabel->setPixmap(QPixmap::fromImage(loadedImage));
    repaint();

    undofunc[currentImageNumber].push(loadedImage);
}


void workingwindow::on_PencilSketch_clicked() //! pencil sketch button clicked, set pencil effect on loaded image
{

    loadedImage = pencil(loadedImage);

    ui->imageLabel->setPixmap(QPixmap::fromImage(loadedImage));
    repaint();

    undofunc[currentImageNumber].push(loadedImage);
}


void workingwindow::on_WarmifyButton_clicked() //! warmify button clicked, set warmify
{
    warm();

    ui->imageLabel->setPixmap(QPixmap::fromImage(loadedImage));
    repaint();

    undofunc[currentImageNumber].push(loadedImage);
}

void workingwindow::on_coolButton_clicked() //! cool button clicked, set cool
{
    cool();

    ui->imageLabel->setPixmap(QPixmap::fromImage(loadedImage));
    repaint();

    undofunc[currentImageNumber].push(loadedImage);
}


void workingwindow::on_saturateButton_clicked() //! saturation button clicked, set saturation
{

    saturate();

    ui->imageLabel->setPixmap(QPixmap::fromImage(loadedImage));
    repaint();

    undofunc[currentImageNumber].push(loadedImage);
}

void workingwindow::on_DesaturateButton_clicked() //! desaturation button clicked, set desaturation
{

    desaturate();

    ui->imageLabel->setPixmap(QPixmap::fromImage(loadedImage));
    repaint();

    undofunc[currentImageNumber].push(loadedImage);
}

void workingwindow::on_overExposeButton_clicked() //! over expose clicked, over expose the image
{

    overExpose();

    ui->imageLabel->setPixmap(QPixmap::fromImage(loadedImage));
    repaint();

    undofunc[currentImageNumber].push(loadedImage);
}

void workingwindow::on_underExposeButton_clicked() //! underexpose clicked, underexpose the image
{
    underExpose();

    ui->imageLabel->setPixmap(QPixmap::fromImage(loadedImage));
    repaint();

    undofunc[currentImageNumber].push(loadedImage);
}

void workingwindow::on_ContrastBoost_clicked() //! contrast clicked, increase the contrast
{

    QImage modded = Boost(loadedImage);

    ui->imageLabel->setPixmap(QPixmap::fromImage(modded));
    repaint();

    undofunc[currentImageNumber].push(modded);
}


void workingwindow::on_ZoomIn_clicked() //! zoom in clicked, zoom image in
{
    picsize = picsize + .25; //! increase scale by 0.25
    scaledImage = loadedImage.scaled(picsize * loadedImage.width(), picsize * loadedImage.height(), Qt::KeepAspectRatio, Qt::FastTransformation);
    ui->imageLabel->setPixmap(QPixmap::fromImage(scaledImage));
    repaint();

}

void workingwindow::on_ZoomOut_clicked() //! zoom out clicked
{
    picsize = picsize - 0.25; //! decrease scale by 0.25
    if (picsize <= 0)
            {
                picsize = 0.25;
            }
    scaledImage = loadedImage.scaled(picsize * loadedImage.width(), picsize * loadedImage.height(), Qt::KeepAspectRatio, Qt::FastTransformation);
    ui->imageLabel->setPixmap(QPixmap::fromImage(scaledImage));
    repaint();
}

void workingwindow::on_Save_clicked() //! save button clicked
{
    QString saveName = QFileDialog::getSaveFileName(this, //! open save dialogue
            tr("Save Image"), "",
            tr("Image file (*.jpg);;All Files (*)"));
    QFile save(saveName);
    QDataStream out(&save);
    out.setVersion(QDataStream::Qt_5_1);
    out << loadedImage;

}

void workingwindow::on_Undo_clicked() //! undo button clicked
{

   if (undofunc[currentImageNumber].hasPic == false)
    {
        currentImageNumber =currentImageNumber - 1; //! decrease stack position
    }

   currentImageNumber = currentImageNumber - 1;

    if(currentImageNumber <= 0)
        {
            currentImageNumber = 0;
        }

    ui->imageLabel->setPixmap(QPixmap::fromImage(undofunc[currentImageNumber].currImg));
    repaint();
    loadedImage = undofunc[currentImageNumber].currImg;
    if(currentImageNumber == 0)
        {
            currentImageNumber = 1;
        }
}

void workingwindow::on_SepiaButton_clicked() //! sepia button clicked, set sepia on loaded image
{
    loadedImage = sepia (loadedImage);

    ui->imageLabel->setPixmap(QPixmap::fromImage(loadedImage));
    repaint();

    undofunc[currentImageNumber].push(loadedImage);
}

void workingwindow::on_PixelateButton_clicked() //! pixelate clicked, set pixelate on loaded image
{
    loadedImage = pixelate(loadedImage);
    ui->imageLabel->setPixmap(QPixmap::fromImage(loadedImage));
    repaint();

    undofunc[currentImageNumber].push(loadedImage);

}

void workingwindow::on_Rotate_clicked() //! rotate the image
{
    QColor oldColor;
    QImage image(loadedImage.height(), loadedImage.width(), QImage::Format_RGB32); //! \var image \brief create an image with inverted dimensions
    image.fill(Qt::white);
    for (int i = 0; i < loadedImage.width(); i++)
    {
        for (int j = 0; j < loadedImage.height(); j++)
        {
                    oldColor = QColor(loadedImage.pixel(i, j));
                    image.setPixel(j,i,qRgb(oldColor.red(), oldColor.green(), oldColor.blue()));

        }
    }
    loadedImage = image;
    ui->imageLabel->setPixmap(QPixmap::fromImage(loadedImage));
    repaint();

    undofunc[currentImageNumber].push(loadedImage);
}

void workingwindow::on_updown_clicked() //! vertically mirror an image
{
    QColor oldColor; //! \var oldColor \brief the colors of the original
    QImage proxy = loadedImage; //! \var proxy \brief set the proxy to your loaded image
    for (int i = 0; i < proxy.width(); i++)
    {
        for (int j = 0; j < proxy.height(); j++)
        {
                    oldColor = QColor(proxy.pixel(i, j));
                    loadedImage.setPixel(i, loadedImage.height() - 1 - j,qRgb(oldColor.red(), oldColor.green(), oldColor.blue())); //! flip pixels vertically

        }
    }
    ui->imageLabel->setPixmap(QPixmap::fromImage(loadedImage));
    repaint();

    undofunc[currentImageNumber].push(loadedImage);
}

void workingwindow::on_leftright_clicked() //! mirror an image horizontally
{
    QColor oldColor; //! \var oldColor \brief store colors from original image
    QImage proxy = loadedImage; //! \var proxy \brief set proxy to loaded image
    for (int i = 0; i < proxy.width(); i++)
    {
        for (int j = 0; j < proxy.height(); j++)
        {
                    oldColor = QColor(proxy.pixel(i, j));
                    loadedImage.setPixel(loadedImage.width() - 1 - i, j,qRgb(oldColor.red(), oldColor.green(), oldColor.blue())); //! flip image pixels horizontally

        }
    }
    ui->imageLabel->setPixmap(QPixmap::fromImage(loadedImage));
    repaint();

    undofunc[currentImageNumber].push(loadedImage);
}


void workingwindow::on_edges_clicked() //! edge detection clicked, set edge detection
{
    loadedImage = edgeDetect(loadedImage);
    ui->imageLabel->setPixmap(QPixmap::fromImage(loadedImage));
    repaint();

    undofunc[currentImageNumber].push(loadedImage);
}

void workingwindow::on_PenButton_toggled(bool checked) //! activate pen button
{

    //bool Pen; // will need to make a global Pen/brush/ect tools...
    if (checked)
    {
        pen = TRUE;
    }
    else
    {
        pen = FALSE;
    }
}

void workingwindow::on_EraserButton_toggled(bool checked) //! activate \ deactivate eraser button
{


    if (checked)
    {
        eraser = TRUE;
        thePen.setColor(Qt::white);
    }
    else
    {
        eraser = FALSE;
    }
}

void workingwindow::on_BrushButton_toggled(bool checked) //! activate \ deactivate brush button
{

    if (checked)
    {
        brush = TRUE;
    }
    else
    {
        brush = FALSE;
    }
}

void workingwindow::mousePressEvent(QMouseEvent *event) //! click the left mouse button
{
    if(event->button() == Qt::LeftButton)
        {
            pointxy = ui->imageLabel->mapFromGlobal(this->mapToGlobal(event->pos())); //! get the current cursor position on the image label

            if(pen == TRUE)
            {
                drawing = TRUE;
            }
            if(eraser == TRUE)
            {
                drawing = TRUE;

            }
            if (brush == TRUE)
            {
                thePen.setColor(Qt::black); //! set the pen to black
                thePen.setWidth(5); //! set the width of the pen
                StaticXY = pointxy;
            }
            if(colorSampler == TRUE)
            {

                QPoint colorPoint = pointxy;
                int x,y;
                x = colorPoint.x();
                y = colorPoint.y();
                x = qBound(0,x, loadedImage.width()-1);
                y = qBound(0,y, loadedImage.height()-1);
                QColor Sample = QColor(loadedImage.pixel(x,y));
                thePen.setColor(Sample);
            }

            if (bucket == TRUE)
            {
                QPoint colorStart = pointxy;
                std::cout << "CALLING START BUCKET";
                doBucket(colorStart);
                ui->imageLabel->setPixmap(QPixmap::fromImage(loadedImage));
                //undofunc[currentImageNumber].push(loadedImage);
            }

        }

}

void workingwindow::mouseMoveEvent(QMouseEvent *event) //! track mouse movement after it is clicked
{
    if(drawing == TRUE)
        {

        //pointxy2 = event->pos();
        pointxy2 = ui->imageLabel->mapFromGlobal(this->mapToGlobal(event->pos())); //! track next point in the label
        drawLine(pointxy2); //! draw a line from mouse down to current point
        ui->imageLabel->setPixmap(QPixmap::fromImage(loadedImage));
        repaint();
        //pointxy = event->pos();
        pointxy = ui->imageLabel->mapFromGlobal(this->mapToGlobal(event->pos())); //! set original point to the current value

        }

}

void workingwindow::mouseReleaseEvent(QMouseEvent *event) //! release the mouse button
{
    if(event->button() == Qt::LeftButton && drawing == TRUE){
        drawing = FALSE;
        undofunc[currentImageNumber].push(loadedImage); //! push the completed line and stop drawing
    }

    if(event->button() == Qt::LeftButton && brush == TRUE)
    {
        StaticXY2 = ui->imageLabel->mapFromGlobal(this->mapToGlobal(event->pos()));
        brush == FALSE;
        QPainter PixPaint (&loadedImage);
        PixPaint.setPen(thePen);
        PixPaint.drawLine(StaticXY, StaticXY2);
        ui->imageLabel->setPixmap(QPixmap::fromImage(loadedImage));
    }
}

void workingwindow::drawLine(QPoint &lastpoint) //! draw a line
{
    if(drawing == TRUE)
    {
        QPainter PixPaint(&loadedImage); //! \var PixPaint \brief set a paint area on the image
        PixPaint.setPen(thePen);
        PixPaint.drawLine(pointxy,lastpoint);
    }
    repaint();

}
void workingwindow::on_Redo_clicked() //! redo action
{
    if (undofunc[currentImageNumber].hasPic == true)
        {
        loadedImage = undofunc[currentImageNumber].currImg;
        ui->imageLabel->setPixmap(QPixmap::fromImage(undofunc[currentImageNumber].currImg));
        repaint();
        currentImageNumber++;
        }
}

void workingwindow::on_Negative_clicked() //! negative button clicked, set negative
{
    loadedImage = negative(loadedImage);

    ui->imageLabel->setPixmap(QPixmap::fromImage(loadedImage));
    repaint();

    undofunc[currentImageNumber].push(loadedImage);

}


void workingwindow::on_OpenNew_clicked() //! open a new image in the work area
{
    QString openNew = QFileDialog::getOpenFileName(this, //! open a new Q dialogue to find image
                       tr("Choose an Image"),"",tr("Images (*.jpg);;All Files (*)"));
    QImage newImage(openNew); //! \var newImage \brief sets a new image from the explorer
    loadedImage = newImage; //! set image to the new iamge

    ui->imageLabel->setPixmap(QPixmap::fromImage(loadedImage));
    repaint();

    undofunc[currentImageNumber].push(loadedImage);
}

void workingwindow::on_lineEdit_returnPressed() //! enter pressed on size tool
{
    loadedImage = loadedImage.scaled(myInputSize * loadedImage.width(), myInputSize * loadedImage.height(), Qt::KeepAspectRatio, Qt::FastTransformation); //! change image scale
    ui->imageLabel->setPixmap(QPixmap::fromImage(loadedImage));
    ui->imageLabel->adjustSize();
    repaint();
}

void workingwindow::on_lineEdit_textEdited(const QString &arg1) //! tool clicked

{
    bool worked;
    myInputSize = arg1.toInt(&worked);
    myInputSize = myInputSize / 100;
}

void workingwindow::on_horizontalSlider_valueChanged(int value) //! horizontal slider values changed
{
    thePen.setWidth(value);
}

void workingwindow::on_colorSample_toggled(bool checked) //! color sample activated
{
    if (checked == TRUE)
    {
        colorSampler = TRUE;
    }
    else
    {
        colorSampler = FALSE;
    }
}

void workingwindow::on_redSlider_valueChanged(int value) //! red slider changed position
{
    int red = value * colorFactor; //! \var red \brief red value stores slider value times color scale factor
    customColor.setRed(red);
    colorPreview.fill(customColor);
    ui->COLORPREVIEW->setPixmap(QPixmap::fromImage(colorPreview));
    thePen.setColor(customColor);
}

void workingwindow::on_greenSlider_valueChanged(int value) //! green slider changed position
{
    int green = value * colorFactor; //! \var green \brief green value stores slider value times color scale factor
    customColor.setGreen(green);
    colorPreview.fill(customColor);
    ui->COLORPREVIEW->setPixmap(QPixmap::fromImage(colorPreview));
    thePen.setColor(customColor);
}

void workingwindow::on_blueSlider_valueChanged(int value) //! blue slider changed position
{
    int blue = value * colorFactor; //! \var blue \brief blue value stores slider value times color scale factor
    customColor.setBlue(blue);
    colorPreview.fill(customColor);
    ui->COLORPREVIEW->setPixmap(QPixmap::fromImage(colorPreview));
    thePen.setColor(customColor);

}

void workingwindow::on_bucket_toggled(bool checked) //! activate \ deactivate bucket tool
{
    if (checked == TRUE)
    {
        bucket = TRUE;
    }
    else
    {
        bucket = FALSE;
    }
}

void workingwindow::on_CropFromLeft_valueChanged(int value) //! set ascpect ratio from the left
{
    QImage proxy = loadedImage; //! \var proxy \brief make a proxy from the loaded image
    double LeftLineFactor = loadedImage.width() / 100; //! \var leftlinefactor \brief sets the scale from left slider
    leftLinePos = value * LeftLineFactor;
    QPen CropDraw; //! \var CropDraw \brief set pen for aspect ratio
    CropDraw.setWidth(10); //! set width
    CropDraw.setColor(Qt::black); //! set pen color to black
    QPainter PixPaint(&loadedImage);
    PixPaint.setPen(thePen);
    QPoint CropStart, CropEnd;
    CropStart.setX(leftLinePos);
    CropStart.setY(0);
    CropEnd.setX(leftLinePos);
    CropEnd.setY(loadedImage.height() -1);
    PixPaint.drawLine(CropStart,CropEnd);
    ui->imageLabel->setPixmap(QPixmap::fromImage(proxy));

}

void workingwindow::on_CropFromRight_valueChanged(int value) //! set ascpect ratio from the right
{
    QImage proxy = loadedImage; //! \var proxy \brief make a proxy from the loaded image
    double LeftLineFactor = loadedImage.width() / 100; //! \var leftlinefactor \brief sets the scale from right slider
    rightLinePos = value * LeftLineFactor;
    QPen CropDraw; //! \var CropDraw \brief set pen for aspect ratio
    CropDraw.setWidth(10); //! set width
    CropDraw.setColor(Qt::black); //! set pen color to black
    QPainter PixPaint(&loadedImage);
    PixPaint.setPen(thePen);
    QPoint CropStart, CropEnd;
    CropStart.setX(rightLinePos);
    CropStart.setY(0);
    CropEnd.setX(rightLinePos);
    CropEnd.setY(loadedImage.height() -1);
    PixPaint.drawLine(CropStart,CropEnd);
    ui->imageLabel->setPixmap(QPixmap::fromImage(proxy));
}

void workingwindow::on_CropFromTop_valueChanged(int value) //! set crop marks from the top
{
    QImage proxy = loadedImage; //! \var proxy \brief make a proxy from the loaded image
    double LeftLineFactor = loadedImage.width() / 100;
    topLinePos = value * LeftLineFactor;
    QPen CropDraw;  //! \var CropDraw \brief set pen for aspect ratio
    CropDraw.setWidth(10); //! set width
    CropDraw.setColor(Qt::black); //! set pen color to black
    QPainter PixPaint(&loadedImage);
    PixPaint.setPen(thePen);
    QPoint CropStart, CropEnd;
    CropStart.setX(0);
    CropStart.setY(topLinePos);
    CropEnd.setX(loadedImage.width()-1);
    CropEnd.setY(topLinePos);
    PixPaint.drawLine(CropStart,CropEnd);
    ui->imageLabel->setPixmap(QPixmap::fromImage(proxy));
}

void workingwindow::on_CropFromDown_valueChanged(int value) //! set crop marks from the bottom
{
    QImage proxy = loadedImage; //! \var proxy \brief make a proxy from the loaded image
    double LeftLineFactor = loadedImage.width() / 100;
    bottomLinePos = value * LeftLineFactor;
    QPen CropDraw; //! \var CropDraw \brief set pen for aspect ratio
    CropDraw.setWidth(10); //! set width
    CropDraw.setColor(Qt::black); //! set pen color to black
    QPainter PixPaint(&loadedImage);
    PixPaint.setPen(thePen);
    QPoint CropStart, CropEnd;
    CropStart.setX(0);
    CropStart.setY(bottomLinePos);
    CropEnd.setX(loadedImage.width() - 1);
    CropEnd.setY(bottomLinePos);
    PixPaint.drawLine(CropStart,CropEnd);
    ui->imageLabel->setPixmap(QPixmap::fromImage(proxy));
}
