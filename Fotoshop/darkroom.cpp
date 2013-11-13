#include "darkroom.h"

void saturate()
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
}

void desaturate()
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
}

void warm()
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
}

void cool()
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

}

void overExpose()
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
}

void underExpose()
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
}
