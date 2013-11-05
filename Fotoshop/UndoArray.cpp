#include "includes.h"
#include "workingwindow.h"

void undoArr::push(QImage file)
    {
    undofunc[currentImageNumber].currImg = file;
    undofunc[currentImageNumber].hasPic = true;
    currentImageNumber = currentImageNumber + 1;
    undofunc[currentImageNumber].hasPic = false;

    }

