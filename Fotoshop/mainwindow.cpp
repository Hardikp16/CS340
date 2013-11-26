/*! \file mainwindow.cpp \brief holds the code that is initially run to output the first GUI window*/
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "workingwindow.h"
#include <direct.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_NewImageButton_clicked(){

    isblank = 1; //! code flags the program to run a new image rather than loading one up
    QDesktopWidget* desktop = qApp->desktop();

    QRect screenGeometry = desktop->screenGeometry();
    screenwidth = screenGeometry.width(); //! store screen width into global var
    screenheight = screenGeometry.height(); //! store screen height into global var

    editor = new workingwindow(this);

    std::cout<<screenwidth<<screenheight<<std::endl;
    editor->setMinimumHeight(screenheight); //! scale new window for full screen mode
    editor->setMinimumWidth(screenwidth);//! scale new window for full screen mode
    editor->showFullScreen();
    this->update();
}

void MainWindow::on_OpenImageButton_clicked()
{
    isblank = 0; //! flag second window to use filename string
    QString fileName = QFileDialog::getOpenFileName(this,
                       tr("Choose an Image"),"",tr("Images (*.jpg);;All Files (*)")); //! collect directory of wanted image and store to string
    filename = fileName;
    QDesktopWidget* desktop = qApp->desktop();
    QRect screenGeometry = desktop->screenGeometry();
    screenwidth = screenGeometry.width();
    screenheight = screenGeometry.height();

    editor = new workingwindow(this);

    std::cout<<screenwidth<<screenheight<<std::endl;
    editor->setMinimumHeight(screenheight);
    editor->setMinimumWidth(screenwidth);
    editor->showFullScreen();
    this->update();
}

void MainWindow::on_ExitButton_clicked()
{
    exit (EXIT_SUCCESS);
}
