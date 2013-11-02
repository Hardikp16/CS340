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
    int newheight = screenheight - 300;
    int newwidth = screenwidth - 300;
    std::cout<<newheight<<newwidth<<std::endl;
    /*! \brief formatting for full screen displays dynamically */
    loadedImage = loadedImage.scaled(newwidth, newheight, Qt::KeepAspectRatio, Qt::FastTransformation);
    ui->imageLabel->setPixmap(QPixmap::fromImage(loadedImage));
    ui->quitButton->adjustSize();
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
