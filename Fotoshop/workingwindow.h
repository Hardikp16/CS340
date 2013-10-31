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
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_6_clicked();

private:
    Ui::workingwindow *ui;
};

#endif // WORKINGWINDOW_H
