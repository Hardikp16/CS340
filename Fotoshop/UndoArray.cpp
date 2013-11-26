/*! \file UndoArray \brief holds the push function of the undo array class*/

#include "includes.h"
#include "workingwindow.h"

void undoArr::push(QImage file) //! \fn push \param file \brief stores an image onto a node
    {
    undofunc[currentImageNumber].currImg = file;
    undofunc[currentImageNumber].hasPic = true;
    currentImageNumber = currentImageNumber + 1;
    undofunc[currentImageNumber].hasPic = false;

    if (currentImageNumber == 254) //! patch up to avoid stack overflow on many operations
    {
        currentImageNumber = 128;
    }

    }

