#include "workingwindow.h"
#include "ui_workingwindow.h"

workingwindow::workingwindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::workingwindow)
{
    ui->setupUi(this);
    /*! creating a proxy to edit with */
    QImage image(filename);
    loadedImage = image;
    int newheight = screenheight ;
    int newwidth = screenwidth ;
    std::cout<<newheight<<newwidth<<std::endl;
    /*! \brief formatting for full screen displays dynamically */
    loadedImage = loadedImage.scaled(newwidth, newheight, Qt::KeepAspectRatio, Qt::FastTransformation);
    ui->imageLabel->setPixmap(QPixmap::fromImage(loadedImage));
    ui->imageLabel->adjustSize();

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
}

void workingwindow::on_Save_clicked()
{

}
