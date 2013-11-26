//! \file filters.cpp \brief C++ code for all of the filter algorithms called in the work area
#include "filters.h"

QImage greyscale(QImage image) //! \fn greyscale \param image \brief takes an image and converts it to grey levels
{
    QColor oldColor;
    for (int i = 0; i < image.width(); i++) //! iterate through width
    {
        for (int j = 0; j < image.height(); j++) //! iterate through height
        {
            oldColor = QColor(image.pixel(i,j)); //! \var oldColor \brief stores the original pixel color
            int averagevalue = (oldColor.red() + oldColor.green() + oldColor.blue())/3; //! \var averagevalue \brief computes the average of RGB values at the current pixels and sets every color to that average
            image.setPixel(i,j,qRgb(averagevalue,averagevalue,averagevalue));
        }
    }

    return image; //! \return image \brief returns the modified image
}

QImage pencil (QImage image) //! \fn pencil \param image \brief filter to make the image look like a pencil sketch
{
    QColor oldColor;
    for (int i = 0; i < image.width(); i++) //! iterate through the width
    {
        for (int j = 0; j < image.height(); j++) //! iterate through the height
        {
            oldColor = QColor(image.pixel(i,j)); //! set the old color value
            int averagevalue = (oldColor.red() + oldColor.green() + oldColor.blue())/3; //! \var averagevalue \brief computes the average like the greyScale algorithm
            if (averagevalue <= 127)
            {
                image.setPixel(i,j,qRgb(0,0,0)); //! sets darker grey values to pure black
            }
            else if (averagevalue >= 128)
            {
                image.setPixel(i,j,qRgb(255,255,255)); //! sets the lighter grey values to pure white
            }
        }
    }
    return image; //! \return image
}

QImage Boost (QImage image) //! \fn Boost \param image \brief function boosts the contrast of an image
{
    QColor oldColor; //! \var oldColor \brief stores the old colors of a pixel
    int red, green, blue, average; //! \var red \var green \var blue \brief stores the RGB values of the image

    for (int i = 0; i < image.width(); i++) //! iterates through the height
    {
        for (int j = 0; j < image.height(); j++) //! iterates through the width
        {
            oldColor = QColor(image.pixel(i,j)); //! sets the old value
            red = oldColor.red(); //! sets the red value
            green = oldColor.green();//! sets the green value
            blue = oldColor.blue(); //! sets the blue value
            average = (red + green + blue) / 3; //! computes the average value of the three
            if (average > 125) //! increases color values of more intense colors
            {
                red = oldColor.red() + 10;
                blue = oldColor.blue() + 10;
                green = oldColor.green() + 10;

                red = qBound(0, red, 255);
                green = qBound(0, green, 255);
                blue = qBound(0, blue, 255);
            }

            else if (average <= 125) //! mutes color values of less intense colors
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
    return image; //! \return image
}

QImage negative (QImage image) //! \fn negative \param iamge \brief changes the image to look like a film negative
{
    QColor oldColor; //! \var oldColor \brief stores the old color values of the image
    int r,g,b;
    for (int i = 0; i < image.width(); i++) //! ieterates width
    {
        for (int j = 0; j < image.height(); j++) //! iterates height
        {

            oldColor = QColor(image.pixel(i,j)); //! sets the old value
            r = oldColor.red() * -1; //! sets red to its negative value
            g = oldColor.green() * -1; //! sets green to its negative value
            b = oldColor.blue() * -1; //! sets blue to its negative value
            image.setPixel(i,j,qRgb(r,g,b)); //! resets pixel into the image
        }
    }
    return image; //! \return image
}

QImage sepia (QImage image) //! \fn sepia \param image \brief sets the image into a sepia tone
{
    QColor oldColor; //! \var oldColor \brief stores the old color value
    int sepia, blue; //! \var sepia \var blue \brief stores sepia and blue set values;
    for (int i = 0; i < image.width(); i++) //! iterate width
    {
        for (int j = 0; j < image.height(); j++) //! iterate height
        {
            oldColor = QColor(image.pixel(i,j));
            int averagevalue = (oldColor.red() + oldColor.green() + oldColor.blue())/3; //! \var averageValue \brief computes the average value like in the grey algorithm
            sepia = averagevalue + 50; //! sets the sepia value to a boosted grey value
            sepia = qBound(0, sepia, 255);
            blue = averagevalue - 50; //! sets the blue value into a darker grey value
            blue = qBound(0, averagevalue, 255);
            image.setPixel(i,j,qRgb(sepia , sepia - 20 , blue)); //! sets red to sepia, green to a darker sepia and blue to a darker grey
        }
    }
    return image; //! \return image
}

QImage edgeDetect (QImage image) //! \fn edgeDetect \param image \brief function that turns the edges white and fills the rest of the image with black
{
    QColor oldColor, oldColor2; //! \var oldColor \var oldColor2 \brief store color values
    int diff, avg, avg2;
    for (int i = 0; i < image.width() -1 ; i++) //! iterate through width
    {
        for (int j = 0; j < image.height() -1; j++) //! iterate through height
        {
                    oldColor = QColor(image.pixel(i, j));
                    oldColor2 = QColor(image.pixel(i + 1, j + 1));
                    avg = (oldColor.red() + oldColor.green() + oldColor.blue()) / 3; //! gets grey value of current pixel
                    avg2 = (oldColor2.red() + oldColor2.blue() + oldColor2.green()) /3;//! gets grey value of adjacent pixel
                    diff = avg - avg2; //! computes the difference between the two values
                    diff = qAbs(diff); //! computes absolute value of the difference
                    if (diff >= 30) //! if the difference is significant, it is an edge, set it to white
                    {
                        image.setPixel(i, j,qRgb(230, 230, 230));
                    }
                    else //! if the difference is not significant, it is a background, set it to black
                    {
                        image.setPixel(i,j,qRgb(0, 0, 0));
                    }
        }
    }
    return image; //! \return image
}

QImage pixelate (QImage image) //! \fn pixelate \param image \brief sets the current image to a pixelated version
{
    image = image.scaled(0.125 *
                                     image.width(), 0.125 * image.height(), Qt::KeepAspectRatio, Qt::FastTransformation); //! shrinks the current image by a value of 8 and overwrites it, high resolution data is lost
    image = image.scaled(8 *
                                     image.width(), 8 * image.height(), Qt::KeepAspectRatio, Qt::FastTransformation); //! takes the shrunken image and blows it back up to its original size

    return image; //! \return image
}
