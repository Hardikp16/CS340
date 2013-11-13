#include "filters.h"

QImage greyscale(QImage image)
{
    QColor oldColor;
    for (int i = 0; i < image.width(); i++)
    {
        for (int j = 0; j < image.height(); j++)
        {
            oldColor = QColor(image.pixel(i,j));
            int averagevalue = (oldColor.red() + oldColor.green() + oldColor.blue())/3;
            image.setPixel(i,j,qRgb(averagevalue,averagevalue,averagevalue));
        }
    }

    return image;
}

QImage pencil (QImage image)
{
    QColor oldColor;
    for (int i = 0; i < image.width(); i++)
    {
        for (int j = 0; j < image.height(); j++)
        {
            oldColor = QColor(image.pixel(i,j));
            int averagevalue = (oldColor.red() + oldColor.green() + oldColor.blue())/3;
            if (averagevalue <= 127)
            {
                image.setPixel(i,j,qRgb(0,0,0));
            }
            else if (averagevalue >= 128)
            {
                image.setPixel(i,j,qRgb(255,255,255));
            }
        }
    }
    return image;
}

QImage Boost (QImage image)
{
    QColor oldColor;
    int red, green, blue, average;

    for (int i = 0; i < image.width(); i++)
    {
        for (int j = 0; j < image.height(); j++)
        {
            oldColor = QColor(image.pixel(i,j));
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
            image.setPixel(i,j,qRgb(red, green ,blue));

        }
    }
    return image;
}

QImage negative (QImage image)
{
    QColor oldColor;
    int r,g,b;
    for (int i = 0; i < image.width(); i++)
    {
        for (int j = 0; j < image.height(); j++)
        {

            oldColor = QColor(image.pixel(i,j));
            r = oldColor.red() * -1;
            g = oldColor.green() * -1;
            b = oldColor.blue() * -1;
            image.setPixel(i,j,qRgb(r,g,b));
        }
    }
    return image;
}

QImage sepia (QImage image)
{
    QColor oldColor;
    int sepia, blue;
    for (int i = 0; i < image.width(); i++)
    {
        for (int j = 0; j < image.height(); j++)
        {
            oldColor = QColor(image.pixel(i,j));
            int averagevalue = (oldColor.red() + oldColor.green() + oldColor.blue())/3;
            sepia = averagevalue + 50;
            sepia = qBound(0, sepia, 255);
            blue = averagevalue - 50;
            blue = qBound(0, averagevalue, 255);
            image.setPixel(i,j,qRgb(sepia , sepia - 20 , blue));
        }
    }
    return image;
}

QImage edgeDetect (QImage image)
{
    QColor oldColor, oldColor2;
    int diff, avg, avg2;
    for (int i = 0; i < image.width() -1 ; i++)
    {
        for (int j = 0; j < image.height() -1; j++)
        {
                    oldColor = QColor(image.pixel(i, j));
                    oldColor2 = QColor(image.pixel(i + 1, j + 1));
                    avg = (oldColor.red() + oldColor.green() + oldColor.blue()) / 3;
                    avg2 = (oldColor2.red() + oldColor2.blue() + oldColor2.green()) /3;
                    diff = avg - avg2;
                    diff = qAbs(diff);
                    if (diff >= 30)
                    {
                        image.setPixel(i, j,qRgb(230, 230, 230));
                    }
                    else
                    {
                        image.setPixel(i,j,qRgb(0, 0, 0));
                    }
        }
    }
    return image;
}

QImage pixelate (QImage image)
{
    image = image.scaled(0.125 *
                                     image.width(), 0.125 * image.height(), Qt::KeepAspectRatio, Qt::FastTransformation);
    image = image.scaled(8 *
                                     image.width(), 8 * image.height(), Qt::KeepAspectRatio, Qt::FastTransformation);

    return image;
}
