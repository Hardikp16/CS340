/*! \header DARKROOM Header File
 *          function constructors for the Darkroom set of tools. */

#include "includes.h"

int paintBucket(int x, int y, QColor toPaint, QColor desiredColor); /*!< Floodfill function*/

void doBucket(QPoint colorStart); /*!<Function to initialize paint bucket */

void saturate(); /*!<Function to saturate the image, takes 0 parameters*/

void desaturate();/*!<Function to desaturate the image, takes 0 parameters*/

void warm();/*!<Function to warm the image, takes 0 parameters*/

void cool();/*!<Function to cool the image, takes 0 parameters*/

void overExpose();/*!<Function to raise exposure, takes 0 parameters*/

void underExpose();/*!<Function to lower exposure, takes 0 parameters*/
