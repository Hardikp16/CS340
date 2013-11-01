#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "workingwindow.h"

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

void MainWindow::on_pushButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                       tr("Choose an Image"),"",tr("Images (*.jpg);;All Files (*)"));
    filename = fileName;
    editor = new workingwindow(this);
    editor->show();
}

void MainWindow::on_pushButton_2_clicked()
{
    exit (EXIT_SUCCESS);
}
