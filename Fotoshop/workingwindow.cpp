#include "workingwindow.h"
#include "ui_workingwindow.h"

workingwindow::workingwindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::workingwindow)
{
    ui->setupUi(this);
    QImage image(filename);
    ui->imageLabel->setPixmap(QPixmap::fromImage(image));
    ui->imageLabel->isVisible();
    std::cout<<"HELLO WORLD";
}

workingwindow::~workingwindow()
{
    delete ui;
}

void workingwindow::on_pushButton_clicked()
{


}

void workingwindow::on_pushButton_2_clicked()
{


}

void workingwindow::on_pushButton_3_clicked()
{


}

void workingwindow::on_pushButton_4_clicked()
{


}

void workingwindow::on_pushButton_5_clicked()
{


}

void workingwindow::on_pushButton_6_clicked()
{


}
