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

    isblank = 1;
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

void MainWindow::on_OpenImageButton_clicked()
{
    isblank = 0;
    QString fileName = QFileDialog::getOpenFileName(this,
                       tr("Choose an Image"),"",tr("Images (*.jpg);;All Files (*)"));
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
