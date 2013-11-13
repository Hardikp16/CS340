#include "workingwindow.h"
#include "ui_workingwindow.h"

workingwindow::workingwindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::workingwindow)
{

    ui->setupUi(this);
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
    exit (EXIT_SUCCESS);
}

void workingwindow::on_greyScale_clicked()
{
    QColor oldColor;
    loadedImage;
    for (int i = 0; i < loadedImage.width(); i++)
    {
        for (int j = 0; j < loadedImage.height(); j++)
        {
            oldColor = QColor(loadedImage.pixel(i,j));
            int averagevalue = (oldColor.red() + oldColor.green() + oldColor.blue())/3;
            loadedImage.setPixel(i,j,qRgb(averagevalue,averagevalue,averagevalue));
        }
    }

    ui->imageLabel->setPixmap(QPixmap::fromImage(loadedImage));
    repaint();

    undofunc[currentImageNumber].push(loadedImage);
}


void workingwindow::on_PencilSketch_clicked()
{
    QColor oldColor;
    loadedImage;
    for (int i = 0; i < loadedImage.width(); i++)
    {
        for (int j = 0; j < loadedImage.height(); j++)
        {
            oldColor = QColor(loadedImage.pixel(i,j));
            int averagevalue = (oldColor.red() + oldColor.green() + oldColor.blue())/3;
            if (averagevalue <= 127)
            {
                loadedImage.setPixel(i,j,qRgb(0,0,0));
            }
            else if (averagevalue >= 128)
            {
                loadedImage.setPixel(i,j,qRgb(255,255,255));
            }
        }
    }

    ui->imageLabel->setPixmap(QPixmap::fromImage(loadedImage));
    repaint();

    undofunc[currentImageNumber].push(loadedImage);
}


void workingwindow::on_WarmifyButton_clicked()
{
    QColor oldColor;
    int red, green;
    loadedImage;
    for (int i = 0; i < loadedImage.width(); i++)
    {
        for (int j = 0; j < loadedImage.height(); j++)
        {
            oldColor = QColor(loadedImage.pixel(i,j));
            red = oldColor.red();
            green = oldColor.green();
            if (oldColor.red() <= 215)
                {
                red = oldColor.red() + 7;
                }
            if (oldColor.green() <= 215)
                {
                green = oldColor.green() + 7;
                }
            loadedImage.setPixel(i,j,qRgb(red, green ,oldColor.blue()));

        }
    }

    ui->imageLabel->setPixmap(QPixmap::fromImage(loadedImage));
    repaint();

    undofunc[currentImageNumber].push(loadedImage);
}

void workingwindow::on_coolButton_clicked()
{
    QColor oldColor;
    int blue;
    loadedImage;
    for (int i = 0; i < loadedImage.width(); i++)
    {
        for (int j = 0; j < loadedImage.height(); j++)
        {
            oldColor = QColor(loadedImage.pixel(i,j));
            blue = oldColor.blue();
            if (oldColor.blue() <= 215)
                {
                blue = oldColor.blue() + 7;
                }
            loadedImage.setPixel(i,j,qRgb(oldColor.red(), oldColor.green(), blue));

        }
    }

    ui->imageLabel->setPixmap(QPixmap::fromImage(loadedImage));
    repaint();

    undofunc[currentImageNumber].push(loadedImage);
}


void workingwindow::on_saturateButton_clicked()
{
    QColor oldColor;
    QColor huesatlit;
    loadedImage;
    int saturation, hue, lightness;
    for (int i = 0; i < loadedImage.width(); i++)
    {
        for (int j = 0; j < loadedImage.height(); j++)
        {
            oldColor = QColor(loadedImage.pixel(i,j));
            huesatlit = oldColor.toHsl();
            saturation = huesatlit.saturation();
            hue = huesatlit.hue();
            lightness = huesatlit.lightness();

            if (saturation < 240)
                {
                    saturation = saturation + 15;
                }
            else
                {
                    saturation = 255;
                }

            huesatlit.setHsl(hue, saturation, lightness);

            loadedImage.setPixel(i,j,qRgb(huesatlit.red(), huesatlit.green() ,huesatlit.blue()));
        }
    }

    ui->imageLabel->setPixmap(QPixmap::fromImage(loadedImage));
    repaint();

    undofunc[currentImageNumber].push(loadedImage);
}

void workingwindow::on_DesaturateButton_clicked()
{
    QColor oldColor;
    QColor huesatlit;
    loadedImage;
    int saturation, hue, lightness;
    for (int i = 0; i < loadedImage.width(); i++)
    {
        for (int j = 0; j < loadedImage.height(); j++)
        {
            oldColor = QColor(loadedImage.pixel(i,j));
            huesatlit = oldColor.toHsl();
            saturation = huesatlit.saturation();
            hue = huesatlit.hue();
            lightness = huesatlit.lightness();

            if (saturation > 15)
                {
                    saturation = saturation - 15;
                }
            else
                {
                    saturation = 0;
                }

            huesatlit.setHsl(hue, saturation, lightness);

            loadedImage.setPixel(i,j,qRgb(huesatlit.red(), huesatlit.green() ,huesatlit.blue()));

        }
    }

    ui->imageLabel->setPixmap(QPixmap::fromImage(loadedImage));
    repaint();

    undofunc[currentImageNumber].push(loadedImage);
}

void workingwindow::on_overExposeButton_clicked()
{
    QColor oldColor;
    QColor huesatlit;
    loadedImage;
    int saturation, hue, lightness;
    for (int i = 0; i < loadedImage.width(); i++)
    {
        for (int j = 0; j < loadedImage.height(); j++)
        {
            oldColor = QColor(loadedImage.pixel(i,j));
            huesatlit = oldColor.toHsl();
            saturation = huesatlit.saturation();
            hue = huesatlit.hue();
            lightness = huesatlit.lightness();

            if (lightness < 240)
                {
                    lightness = lightness + 15;
                }
            else
                {
                    lightness = 255;
                }

            huesatlit.setHsl(hue, saturation, lightness);

            loadedImage.setPixel(i,j,qRgb(huesatlit.red(), huesatlit.green() ,huesatlit.blue()));

        }
    }

    ui->imageLabel->setPixmap(QPixmap::fromImage(loadedImage));
    repaint();

    undofunc[currentImageNumber].push(loadedImage);
}

void workingwindow::on_underExposeButton_clicked()
{
    QColor oldColor;
    QColor huesatlit;
    loadedImage;
    int saturation, hue, lightness;
    for (int i = 0; i < loadedImage.width(); i++)
    {
        for (int j = 0; j < loadedImage.height(); j++)
        {
            oldColor = QColor(loadedImage.pixel(i,j));
            huesatlit = oldColor.toHsl();
            saturation = huesatlit.saturation();
            hue = huesatlit.hue();
            lightness = huesatlit.lightness();

            if (lightness > 15)
                {
                    lightness = lightness - 15;
                }
            else
                {
                    lightness = 0;
                }
            huesatlit.setHsl(hue, saturation, lightness);

            loadedImage.setPixel(i,j,qRgb(huesatlit.red(), huesatlit.green() ,huesatlit.blue()));

        }
    }

    ui->imageLabel->setPixmap(QPixmap::fromImage(loadedImage));
    repaint();

    undofunc[currentImageNumber].push(loadedImage);
}

void workingwindow::on_ContrastBoost_clicked()
{
    QColor oldColor;
    loadedImage;
    int red, green, blue, average;
    for (int i = 0; i < loadedImage.width(); i++)
    {
        for (int j = 0; j < loadedImage.height(); j++)
        {
            oldColor = QColor(loadedImage.pixel(i,j));
            red = oldColor.red();
            green = oldColor.green();
            blue = oldColor.blue();
            average = (red + green + blue) / 3;
            if (average > 125)
            {
                red = oldColor.red() + 10;
                blue = oldColor.blue() + 10;
                green = oldColor.green() + 10;

                red = qBound(0, red, 255);
                green = qBound(0, green, 255);
                blue = qBound(0, blue, 255);
            }

            else if (average <= 125)
            {
                red = oldColor.red() - 10;
                blue = oldColor.blue() - 10;
                green = oldColor.green() - 10;

                red = qBound(0, red, 255);
                green = qBound(0, green, 255);
                blue = qBound(0, blue, 255);
            }
            loadedImage.setPixel(i,j,qRgb(red, green ,blue));

        }
    }

    ui->imageLabel->setPixmap(QPixmap::fromImage(loadedImage));
    repaint();

    undofunc[currentImageNumber].push(loadedImage);
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
    QColor oldColor;
    loadedImage;
    int sepia, blue;
    for (int i = 0; i < loadedImage.width(); i++)
    {
        for (int j = 0; j < loadedImage.height(); j++)
        {
            oldColor = QColor(loadedImage.pixel(i,j));
            int averagevalue = (oldColor.red() + oldColor.green() + oldColor.blue())/3;
            sepia = averagevalue + 50;
            sepia = qBound(0, sepia, 255);
            blue = averagevalue - 50;
            blue = qBound(0, averagevalue, 255);
            loadedImage.setPixel(i,j,qRgb(sepia , sepia - 20 , blue));
        }
    }

    ui->imageLabel->setPixmap(QPixmap::fromImage(loadedImage));
    repaint();

    undofunc[currentImageNumber].push(loadedImage);
}

void workingwindow::on_PixelateButton_clicked()
{
    loadedImage = loadedImage.scaled(0.125 * loadedImage.width(), 0.125 * loadedImage.height(), Qt::KeepAspectRatio, Qt::FastTransformation);
    loadedImage = loadedImage.scaled(8 * loadedImage.width(), 8 * loadedImage.height(), Qt::KeepAspectRatio, Qt::FastTransformation);
    ui->imageLabel->setPixmap(QPixmap::fromImage(loadedImage));
    repaint();

    undofunc[currentImageNumber].push(loadedImage);

}

void workingwindow::on_Rotate_clicked()
{
    QColor oldColor;
    loadedImage;
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
    QColor oldColor, oldColor2;
    QImage proxy = loadedImage;
    int diff, avg, avg2;
    for (int i = 0; i < proxy.width() -1 ; i++)
    {
        for (int j = 0; j < proxy.height() -1; j++)
        {
                    oldColor = QColor(proxy.pixel(i, j));
                    oldColor2 = QColor(proxy.pixel(i + 1, j + 1));
                    avg = (oldColor.red() + oldColor.green() + oldColor.blue()) / 3;
                    avg2 = (oldColor2.red() + oldColor2.blue() + oldColor2.green()) /3;
                    diff = avg - avg2;
                    diff = qAbs(diff);
                    if (diff >= 30)
                    {
                        loadedImage.setPixel(i, j,qRgb(230, 230, 230));
                    }
                    else
                    {
                        loadedImage.setPixel(i,j,qRgb(0, 0, 0));
                    }
        }
    }
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
    QColor oldColor;
    loadedImage;
    int r,g,b;
    for (int i = 0; i < loadedImage.width(); i++)
    {
        for (int j = 0; j < loadedImage.height(); j++)
        {

            oldColor = QColor(loadedImage.pixel(i,j));
            r = oldColor.red() * -1;
            g = oldColor.green() * -1;
            b = oldColor.blue() * -1;
            loadedImage.setPixel(i,j,qRgb(r,g,b));
        }
    }

    ui->imageLabel->setPixmap(QPixmap::fromImage(loadedImage));
    repaint();

    undofunc[currentImageNumber].push(loadedImage);

}
