#ifndef WORKINGWINDOW_H
#define WORKINGWINDOW_H

#include "includes.h"

extern undoArr undofunc[256];

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

    void on_Save_clicked();

    void on_ZoomOut_clicked();

    void on_Undo_clicked();

    void on_SepiaButton_clicked();

    void on_PixelateButton_clicked();

    void on_Rotate_clicked();

    void on_updown_clicked();

    void on_leftright_clicked();

    void on_edges_clicked();

    void on_PenButton_toggled(bool checked);

private:
    Ui::workingwindow *ui;
};

#endif // WORKINGWINDOW_H
