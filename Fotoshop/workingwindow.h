#ifndef WORKINGWINDOW_H
#define WORKINGWINDOW_H

#include "includes.h"

namespace Ui {
class workingwindow;
}

class workingwindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit workingwindow(QWidget *parent = 0);
    ~workingwindow();

private slots:


    void on_quitButton_clicked();

    void on_greyScale_clicked();

    void on_PencilSketch_clicked();

    void on_WarmifyButton_clicked();

    void on_coolButton_clicked();

    void on_saturateButton_clicked();

    void on_DesaturateButton_clicked();

    void on_overExposeButton_clicked();

    void on_underExposeButton_clicked();

    void on_ContrastBoost_clicked();

    void on_ZoomIn_clicked();

    void on_pushButton_clicked();

    void on_Save_clicked();

private:
    Ui::workingwindow *ui;
};

#endif // WORKINGWINDOW_H
