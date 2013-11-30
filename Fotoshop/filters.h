/*! \header Header for the photofilters */

#include "includes.h"

QImage greyscale ( QImage image); /*! \fn function constructor greyscale( QImage ) turns the loaded image grey */

QImage pencil (QImage image); /*! \fn function constructor pencil( QImage ) turns the loaded image into a pencil sketch */

QImage negative (QImage image);/*! \fn function contsturctor negative( QImage ) turns the loaded image negative */

QImage Boost (QImage image);/*! \fn function constructor boost( QImage ) raises the image contrast */

QImage sepia (QImage image);/*! \fn function sepia( QImage ) turns the loaded image sepia */

QImage edgeDetect (QImage image);/*! \fn function edges( QImage ) turns edges white and the rest black*/

QImage pixelate (QImage image);/*! \fn function pixelate( QImage ) pixelates the image*/
