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

private:
    Ui::workingwindow *ui;
};

#endif // WORKINGWINDOW_H
