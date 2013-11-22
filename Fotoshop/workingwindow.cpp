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

    /*! creating a proxy to edit with */
    if (isblank == 1)
        {
        QImage image(1920, 1080, QImage::Format_RGB32);
            image.fill(Qt::white);
            loadedImage = image;
        }
    else
    {
        QImage image(filename);
        loadedImage = image;
    }
    QImage temp2(270, 115, QImage::Format_RGB32);
    temp2.fill(Qt::black);
    colorPreview = temp2;
    ui->COLORPREVIEW->setPixmap(QPixmap::fromImage(colorPreview));


    colorFactor = 2.55;

    ui->horizontalSlider->setValue(25);
    QImage temp(":/Icon/color_wheel1.png");
    ColorWheel = temp;
    ColorWheel = ColorWheel.scaled(screenwidth / 4, screenheight / 4, Qt::KeepAspectRatio, Qt::FastTransformation);

    ui->colorWheel->setPixmap(QPixmap::fromImage(ColorWheel));
    ui->imageLabel->setPixmap(QPixmap::fromImage(loadedImage));
    ui->imageLabel->adjustSize();

    undofunc[0].push(loadedImage);
    undoVector.push_back(loadedImage);
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

void workingwindow::on_greyScale_clicked()
{
    loadedImage = greyscale(loadedImage);

    ui->imageLabel->setPixmap(QPixmap::fromImage(loadedImage));
    repaint();

    undofunc[currentImageNumber].push(loadedImage);
}


void workingwindow::on_PencilSketch_clicked()
{

    loadedImage = pencil(loadedImage);

    ui->imageLabel->setPixmap(QPixmap::fromImage(loadedImage));
    repaint();

    undofunc[currentImageNumber].push(loadedImage);
}


void workingwindow::on_WarmifyButton_clicked()
{
    warm();

    ui->imageLabel->setPixmap(QPixmap::fromImage(loadedImage));
    repaint();

    undofunc[currentImageNumber].push(loadedImage);
}

void workingwindow::on_coolButton_clicked()
{
    cool();

    ui->imageLabel->setPixmap(QPixmap::fromImage(loadedImage));
    repaint();

    undofunc[currentImageNumber].push(loadedImage);
}


void workingwindow::on_saturateButton_clicked()
{

    saturate();

    ui->imageLabel->setPixmap(QPixmap::fromImage(loadedImage));
    repaint();

    undofunc[currentImageNumber].push(loadedImage);
}

void workingwindow::on_DesaturateButton_clicked()
{

    desaturate();

    ui->imageLabel->setPixmap(QPixmap::fromImage(loadedImage));
    repaint();

    undofunc[currentImageNumber].push(loadedImage);
}

void workingwindow::on_overExposeButton_clicked()
{

    overExpose();

    ui->imageLabel->setPixmap(QPixmap::fromImage(loadedImage));
    repaint();

    undofunc[currentImageNumber].push(loadedImage);
}

void workingwindow::on_underExposeButton_clicked()
{
    underExpose();

    ui->imageLabel->setPixmap(QPixmap::fromImage(loadedImage));
    repaint();

    undofunc[currentImageNumber].push(loadedImage);
}

void workingwindow::on_ContrastBoost_clicked()
{

    QImage modded = Boost(loadedImage);

    ui->imageLabel->setPixmap(QPixmap::fromImage(modded));
    repaint();

    undofunc[currentImageNumber].push(modded);
}


void workingwindow::on_ZoomIn_clicked()
{
    picsize = picsize + .25;
    scaledImage = loadedImage.scaled(picsize * loadedImage.width(), picsize * loadedImage.height(), Qt::KeepAspectRatio, Qt::FastTransformation);
    ui->imageLabel->setPixmap(QPixmap::fromImage(scaledImage));
    repaint();

}

void workingwindow::on_ZoomOut_clicked()
{
    picsize = picsize - 0.25;
    if (picsize <= 0)
            {
                picsize = 0.25;
            }
    scaledImage = loadedImage.scaled(picsize * loadedImage.width(), picsize * loadedImage.height(), Qt::KeepAspectRatio, Qt::FastTransformation);
    ui->imageLabel->setPixmap(QPixmap::fromImage(scaledImage));
    repaint();
}

void workingwindow::on_Save_clicked()
{
    QString saveName = QFileDialog::getSaveFileName(this,
            tr("Save Image"), "",
            tr("Image file (*.jpg);;All Files (*)"));
    QFile save(saveName);
    QDataStream out(&save);
    out.setVersion(QDataStream::Qt_5_1);
    out << loadedImage;

}

void workingwindow::on_Undo_clicked()
{

   if (undofunc[currentImageNumber].hasPic == false)
    {
        currentImageNumber =currentImageNumber - 1;
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

void workingwindow::on_SepiaButton_clicked()
{
    loadedImage = sepia (loadedImage);

    ui->imageLabel->setPixmap(QPixmap::fromImage(loadedImage));
    repaint();

    undofunc[currentImageNumber].push(loadedImage);
}

void workingwindow::on_PixelateButton_clicked()
{
    loadedImage = pixelate(loadedImage);
    ui->imageLabel->setPixmap(QPixmap::fromImage(loadedImage));
    repaint();

    undofunc[currentImageNumber].push(loadedImage);

}

void workingwindow::on_Rotate_clicked()
{
    QColor oldColor;
    QImage image(loadedImage.height(), loadedImage.width(), QImage::Format_RGB32);
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

void workingwindow::on_updown_clicked()
{
    QColor oldColor;
    QImage proxy = loadedImage;
    for (int i = 0; i < proxy.width(); i++)
    {
        for (int j = 0; j < proxy.height(); j++)
        {
                    oldColor = QColor(proxy.pixel(i, j));
                    loadedImage.setPixel(i, loadedImage.height() - 1 - j,qRgb(oldColor.red(), oldColor.green(), oldColor.blue()));

        }
    }
    ui->imageLabel->setPixmap(QPixmap::fromImage(loadedImage));
    repaint();

    undofunc[currentImageNumber].push(loadedImage);
}

void workingwindow::on_leftright_clicked()
{
    QColor oldColor;
    QImage proxy = loadedImage;
    for (int i = 0; i < proxy.width(); i++)
    {
        for (int j = 0; j < proxy.height(); j++)
        {
                    oldColor = QColor(proxy.pixel(i, j));
                    loadedImage.setPixel(loadedImage.width() - 1 - i, j,qRgb(oldColor.red(), oldColor.green(), oldColor.blue()));

        }
    }
    ui->imageLabel->setPixmap(QPixmap::fromImage(loadedImage));
    repaint();

    undofunc[currentImageNumber].push(loadedImage);
}


void workingwindow::on_edges_clicked()
{
    loadedImage = edgeDetect(loadedImage);
    ui->imageLabel->setPixmap(QPixmap::fromImage(loadedImage));
    repaint();

    undofunc[currentImageNumber].push(loadedImage);
}

void workingwindow::on_PenButton_toggled(bool checked)
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

void workingwindow::on_EraserButton_toggled(bool checked)
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

void workingwindow::on_BrushButton_toggled(bool checked)
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

void workingwindow::on_TextButton_toggled(bool checked)
{

    if (checked)
    {
        text = TRUE;
    }
    else
    {
        text = FALSE;
    }
}

void workingwindow::mousePressEvent(QMouseEvent *event)
{
    //this->paintArea(event->x(), event->y());
    if(event->button() == Qt::LeftButton)
        {
            //int pointx,pointy;
            if(pen == TRUE)
            {
                pointxy = ui->imageLabel->mapFromGlobal(this->mapToGlobal(event->pos()));
                drawing = TRUE;
            }
            if(eraser == TRUE)
            {
                pointxy = ui->imageLabel->mapFromGlobal(this->mapToGlobal(event->pos()));
                drawing = TRUE;

            }
            if(colorSampler == TRUE)
            {

                QPoint colorPoint = ui->imageLabel->mapFromGlobal(this->mapToGlobal(event->pos()));
                int x,y;
                x = colorPoint.x();
                y = colorPoint.y();
                x = qBound(0,x, loadedImage.width());
                y = qBound(0,y, loadedImage.height());
                QColor Sample = QColor(loadedImage.pixel(x,y));
                thePen.setColor(Sample);
            }
            if (brush = TRUE)
            {
              /*  std::cout << "ENTERED COLOR CHOOSER MODE!";
                //enter color chooser mode.
                QPoint colorPoint = ui->colorWheel->mapFromGlobal(this->mapToGlobal(event->pos()));
                int x,y;
                x = colorPoint.x();
                y = colorPoint.y();
                x = qBound(0,x, ColorWheel.width());
                y = qBound(0,y, ColorWheel.height());
                QColor ChooseColor = QColor(ColorWheel.pixel(x,y));
                thePen.setColor(ChooseColor);
                */
              }
        }

}

void workingwindow::mouseMoveEvent(QMouseEvent *event)
{
    if(drawing == TRUE)
        {

        //pointxy2 = event->pos();
        pointxy2 = ui->imageLabel->mapFromGlobal(this->mapToGlobal(event->pos()));
        drawLine(pointxy2);
        ui->imageLabel->setPixmap(QPixmap::fromImage(loadedImage));
        repaint();
        //pointxy = event->pos();
        pointxy = ui->imageLabel->mapFromGlobal(this->mapToGlobal(event->pos()));

        }

}

void workingwindow::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton && drawing == TRUE){
        drawing = FALSE;
    }
}

void workingwindow::drawLine(QPoint &lastpoint)
{
    if(drawing == TRUE)
    {
        QPainter PixPaint(&loadedImage);
        //QBrush brush(Qt::black, Qt::SolidPattern);
        PixPaint.setPen(thePen);
        PixPaint.drawLine(pointxy,lastpoint);
    }
    repaint();

}
void workingwindow::on_Redo_clicked()
{
    if (undofunc[currentImageNumber].hasPic == true)
        {
        ui->imageLabel->setPixmap(QPixmap::fromImage(undofunc[currentImageNumber].currImg));
        repaint();
        currentImageNumber++;
        }
}

void workingwindow::on_Negative_clicked()
{
    loadedImage = negative(loadedImage);

    ui->imageLabel->setPixmap(QPixmap::fromImage(loadedImage));
    repaint();

    undofunc[currentImageNumber].push(loadedImage);

}


void workingwindow::on_OpenNew_clicked()
{
    QString openNew = QFileDialog::getOpenFileName(this,
                       tr("Choose an Image"),"",tr("Images (*.jpg);;All Files (*)"));
    QImage newImage(openNew);
    loadedImage = newImage;

    ui->imageLabel->setPixmap(QPixmap::fromImage(loadedImage));
    repaint();

    undofunc[currentImageNumber].push(loadedImage);
}

void workingwindow::on_lineEdit_returnPressed()
{
    loadedImage = loadedImage.scaled(myInputSize * loadedImage.width(), myInputSize * loadedImage.height(), Qt::KeepAspectRatio, Qt::FastTransformation);
    ui->imageLabel->setPixmap(QPixmap::fromImage(loadedImage));
    repaint();
}

void workingwindow::on_lineEdit_textEdited(const QString &arg1)

{
    bool worked;
    myInputSize = arg1.toInt(&worked);
    myInputSize = myInputSize / 100;
}

void workingwindow::on_horizontalSlider_valueChanged(int value)
{
    thePen.setWidth(value);
}

void workingwindow::on_colorSample_toggled(bool checked)
{
    if (checked)
    {
        colorSampler = TRUE;
    }
    else
    {
        colorSampler = FALSE;
    }
}

void workingwindow::on_redSlider_valueChanged(int value)
{
    int red = value * colorFactor;
    customColor.setRed(red);
    colorPreview.fill(customColor);
    ui->COLORPREVIEW->setPixmap(QPixmap::fromImage(colorPreview));
    thePen.setColor(customColor);
}

void workingwindow::on_greenSlider_valueChanged(int value)
{
    int green = value * colorFactor;
    customColor.setGreen(green);
    colorPreview.fill(customColor);
    ui->COLORPREVIEW->setPixmap(QPixmap::fromImage(colorPreview));
    thePen.setColor(customColor);
}

void workingwindow::on_blueSlider_valueChanged(int value)
{
    int blue = value * colorFactor;\
    customColor.setBlue(blue);
    colorPreview.fill(customColor);
    ui->COLORPREVIEW->setPixmap(QPixmap::fromImage(colorPreview));
    thePen.setColor(customColor);

}
