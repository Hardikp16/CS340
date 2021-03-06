/*! \header MainWindow \brief the header file for the small new / load / close window */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "workingwindow.h"
#include "includes.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:
    //! slots for the new/open/exit pushbuttons.
    void on_NewImageButton_clicked();
    void on_OpenImageButton_clicked();
    void on_ExitButton_clicked();

private:
    Ui::MainWindow *ui;
    workingwindow *editor;

};

#endif // MAINWINDOW_H
