/*! \file Darkroom
 *          \brief contains all of the actual actions in the darkroom toolset */

#include "darkroom.h"
#include <thread>

void saturate() //! \fn saturate \brief saturate takes the saturation value from the HSL of every individual pixel and increases it.
{
    QColor oldColor; //! \var QColor oldColor \brief the original color of the current pixel
    QColor huesatlit; //! \var huesatlit \brief an HSL representation of oldcolor's rgb values
    loadedImage;
    int saturation, hue, lightness; //! \var int saturation \brief stores saturation \var int hue \brief stores hue \var lightness \brief stores lightness
    for (int i = 0; i < loadedImage.width(); i++) //! iterates through pixels from 0 to max width
    {
        for (int j = 0; j < loadedImage.height(); j++) //! iterates through pixels from 0 to max height
        {
            oldColor = QColor(loadedImage.pixel(i,j)); //! takes colors from each position and stores to a variable
            huesatlit = oldColor.toHsl(); //! takes hue/saturation/lightness from each color
            saturation = huesatlit.saturation();
            hue = huesatlit.hue();
            lightness = huesatlit.lightness();

            if (saturation < 240) //! if the saturation is below 240, increase it to a maximum of 255,  else do nothing.
                {
                    saturation = saturation + 15;
                }
            else
                {
                    saturation = 255;
                }

            huesatlit.setHsl(hue, saturation, lightness);

            loadedImage.setPixel(i,j,qRgb(huesatlit.red(), huesatlit.green() ,huesatlit.blue())); //! reset the image with new color values
        }
    }
}

void desaturate() //! \fn destaturate \brief similar to the saturation function, except decreases values rather than increasing
{
    QColor oldColor; //! \var QColor oldColor \brief the original color of the current pixel
    QColor huesatlit; //! \var huesatlit \brief an HSL representation of oldcolor's rgb values
    loadedImage;
    int saturation, hue, lightness; //! \var int saturation \brief stores saturation \var int hue \brief stores hue \var lightness \brief stores lightness
    for (int i = 0; i < loadedImage.width(); i++)//! iterates through pixels from 0 to max width
    {
        for (int j = 0; j < loadedImage.height(); j++)//! iterates through pixels from 0 to max height
        {
            oldColor = QColor(loadedImage.pixel(i,j));
            huesatlit = oldColor.toHsl();
            saturation = huesatlit.saturation();
            hue = huesatlit.hue();
            lightness = huesatlit.lightness();

            if (saturation > 15) //! changes saturation to a decreased value with a minimum of 0 by incremements of 15
                {
                    saturation = saturation - 15;
                }
            else
                {
                    saturation = 0;
                }

            huesatlit.setHsl(hue, saturation, lightness);

            loadedImage.setPixel(i,j,qRgb(huesatlit.red(), huesatlit.green() ,huesatlit.blue())); //! resets the image with new color values

        }
    }
}

void warm() //! \fn void warm \brief function that changes changes the image white balance to warmer
{
    QColor oldColor; //! \var QColor oldColor \brief stores the original color of the desired pixel
    int red, green; //! \var int red \var int green \brief stores the red and green values of the desired pixel
    loadedImage;
    for (int i = 0; i < loadedImage.width(); i++) //! iterate through the width
    {
        for (int j = 0; j < loadedImage.height(); j++)//! iterate through the height
        {
            oldColor = QColor(loadedImage.pixel(i,j));//! store old pixel values
            red = oldColor.red();
            green = oldColor.green();
            if (oldColor.red() <= 215) //! boost low red tones in the image
                {
                red = oldColor.red() + 7;
                }
            if (oldColor.green() <= 215) //! boost low green tones in the image
                {
                green = oldColor.green() + 7;
                }
            loadedImage.setPixel(i,j,qRgb(red, green ,oldColor.blue()));//! reset the image with its new values

        }
    }
}

void cool() //! void cool \brief function that changes the image white balance to cooler
{
    QColor oldColor; //! \var oldColor \brief stores the old value of the pixel
    int blue; //! \var int blue \brief stores the blue values of the pixels
    loadedImage;
    for (int i = 0; i < loadedImage.width(); i++) //! iterates through the width
    {
        for (int j = 0; j < loadedImage.height(); j++) //! iterates through the height
        {
            oldColor = QColor(loadedImage.pixel(i,j));
            blue = oldColor.blue();
            if (oldColor.blue() <= 215) //! boost low blue levels within an image
                {
                blue = oldColor.blue() + 7;
                }
            loadedImage.setPixel(i,j,qRgb(oldColor.red(), oldColor.green(), blue));

        }
    }

}

void overExpose() //! \fn void overExpose \brief function to raise the exposure of an image
{
    QColor oldColor; //! \var QColor oldColor \brief stores old color values
    QColor huesatlit;
    loadedImage;
    int saturation, hue, lightness;//! \var saturation \var hue \var lightness \brief stores the HSL values of the pixels
    for (int i = 0; i < loadedImage.width(); i++) //! iterates through the width
    {
        for (int j = 0; j < loadedImage.height(); j++) //! iterates through the height
        {
            oldColor = QColor(loadedImage.pixel(i,j));
            huesatlit = oldColor.toHsl(); //! converts pixels to their HSL values
            saturation = huesatlit.saturation();
            hue = huesatlit.hue();
            lightness = huesatlit.lightness();

            if (lightness < 240) //! boosts low lightness levels in an image
                {
                    lightness = lightness + 15;
                }
            else
                {
                    lightness = 255;
                }

            huesatlit.setHsl(hue, saturation, lightness);

            loadedImage.setPixel(i,j,qRgb(huesatlit.red(), huesatlit.green() ,huesatlit.blue())); //! resets image with new values

        }
    }
}

void underExpose() //! \fn underExpose \brief function to lower the exposure of an image
{
    QColor oldColor; //! \var QColor oldColor \brief stores the color values of the pixel
    QColor huesatlit;
    loadedImage;
    int saturation, hue, lightness; //! \var hue \var lightness \var saturation \brief stores the HSL values in the pixel
    for (int i = 0; i < loadedImage.width(); i++) //! iterate through the width
    {
        for (int j = 0; j < loadedImage.height(); j++) //! iterate through the height
        {
            oldColor = QColor(loadedImage.pixel(i,j));
            huesatlit = oldColor.toHsl();
            saturation = huesatlit.saturation();
            hue = huesatlit.hue();
            lightness = huesatlit.lightness();

            if (lightness > 15) //! reset the lightness to a lower value
                {
                    lightness = lightness - 15;
                }
            else
                {
                    lightness = 0;
                }
            huesatlit.setHsl(hue, saturation, lightness);

            loadedImage.setPixel(i,j,qRgb(huesatlit.red(), huesatlit.green() ,huesatlit.blue())); //! reset the image with new values

        }
    }
}

void doBucket(QPoint colorStart) //! \fn void doBucket \brief runner for the bucket fill tool
{
    int initX, initY; //! \var int initX \var int initY \brief stores the starting x and y positions of the algorithm
    initX = colorStart.x();
    initY = colorStart.y();
    std:: cout << initX << initY <<std ::endl;
    initX = qBound(0,initX, loadedImage.width()-1); //! size contraints to stay within boundry
    initY = qBound(0,initY, loadedImage.height()-1);
    QColor initColor = QColor(loadedImage.pixel(initX,initY));
    std :: cout << "about to call function paintBucket";
    paintBucket(initX, initY, initColor, thePen.color()); //! call to the actual paint bucket function
}

int paintBucket (int xInFunction, int yInFunction, QColor toPaint, QColor desiredColor) //! \fn int paintbucket \param int X \param int y \param QColortoPaint \param QColor desiredColor
{
    bool done = FALSE; //! function is not done
    if (done == TRUE)
    {
        std :: cout << "crash1"<< std::endl;

        return 0; //! end the recursion on this

    }
    else
    {

        if (yInFunction == 0)
        {
            std :: cout << "crash?2"<< std::endl;

        done = TRUE;
        return 0; //! end the recursion by boundry
        }

        else if (xInFunction == 0)
        {
            std :: cout << "crash?3"<< std::endl;

        done = TRUE;
        return 0;//! end the recursion by boundry
        }
        else
        {

            QColor currentColor = QColor(loadedImage.pixel(xInFunction,yInFunction)); //! QColor currentColor \brief stores the color of the current position

            if ((xInFunction > 0) && (xInFunction < 50) &&
                    ((yInFunction > 0) && (yInFunction < 50) &&
                    currentColor.red() == toPaint.red()
                    && currentColor.blue() == toPaint.blue() && currentColor.green() == toPaint.green()))
                {
                std :: cout << "loop"<< std::endl;

                    loadedImage.setPixel(xInFunction,yInFunction, qRgb(desiredColor.red(), desiredColor.green(), desiredColor.blue())); //! sets current position to the new color

                    return (paintBucket(xInFunction, yInFunction-1, toPaint, desiredColor) + paintBucket(xInFunction-1, yInFunction, toPaint, desiredColor) +
                            paintBucket(xInFunction, yInFunction+1, toPaint, desiredColor) + paintBucket(xInFunction+1, yInFunction, toPaint, desiredColor));
                    }
        }
    }
}
