#include "workingwindow.h"
#include "ui_workingwindow.h"
#include "filters.h"
#include "darkroom.h"

workingwindow::workingwindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::workingwindow)
{

    ui->setupUi(this);
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
    int newheight = screenheight-200 ;
    int newwidth = screenwidth-200 ;
    std::cout<<newheight<<newwidth<<std::endl;
    /*! \brief formatting for full screen displays dynamically */
    loadedImage = loadedImage.scaled(newwidth, newheight, Qt::KeepAspectRatio, Qt::FastTransformation);
    ui->imageLabel->setPixmap(QPixmap::fromImage(loadedImage));
    ui->imageLabel->adjustSize();

    ui->scrollArea->setBackgroundRole(QPalette::Dark);

    undofunc[0].push(loadedImage);

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
        std::cout<<"on"<<std::endl;
    }
    else
    {
        pen = FALSE;
        std::cout<<"off"<<std::endl;
    }
}

void workingwindow::on_EraserButton_toggled(bool checked)
{
    if (checked)
    {
        eraser = TRUE;
        std::cout<<"on"<<std::endl;
    }
    else
    {
        eraser = FALSE;
        std::cout<<"off"<<std::endl;
    }
}

void workingwindow::on_BrushButton_toggled(bool checked)
{
    if (checked)
    {
        brush = TRUE;
        std::cout<<"on"<<std::endl;
    }
    else
    {
        brush = FALSE;
        std::cout<<"off"<<std::endl;
    }
}

void workingwindow::on_TextButton_toggled(bool checked)
{
    if (checked)
    {
        text = TRUE;
        std::cout<<"on"<<std::endl;
    }
    else
    {
        text = FALSE;
        std::cout<<"off"<<std::endl;
    }
}


void workingwindow::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
        {
            int pointx,pointy;
            if(pen == TRUE)
            {
                std::cout<< "Paint is on and now going to track the mouse and start drawing" <<std::endl;
                pointxy = event->pos();
                pointx = pointxy.x();
                pointy = pointxy.y();
                std::cout << pointx;
                std::cout << " " << pointy << std::endl;
                drawing = TRUE;
            }
        }
}

void workingwindow::mouseMoveEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton && drawing == TRUE)
        {
            std::cout<< "I can paint & move" <<std::endl;
        }
}

void workingwindow::mouseReleaseEvent(QMouseEvent *event)
{
    drawing = FALSE; //
    pointxy2 = event->pos();
    std::cout<< "mouse button released and stop drawing" <<std::endl;

}

void workingwindow::paintEvent(QPaintEvent *event){ // gives 3 errors Painter not active, Paintengine should be called,
    if(pen == TRUE){
        QPainter painter(ui->imageLabel);
        //painter.drawPixmap(screenheight,screenwidth,*buffer);
        QPen pendraw(Qt::black);
        painter.setPen(pendraw);
        painter.drawLine(pointxy,pointxy2);

    }
}

void workingwindow::on_Redo_clicked()
{
    if (undofunc[currentImageNumber + 1].hasPic == true)
        {
        ui->imageLabel->setPixmap(QPixmap::fromImage(undofunc[currentImageNumber + 1].currImg));
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
