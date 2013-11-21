#ifndef WORKINGWINDOW_H
#define WORKINGWINDOW_H

#include "includes.h"

extern undoArr *undofunc;

extern std::vector<QImage> undoVector;

extern double myInputSize;

namespace Ui {
class workingwindow;
}

class workingwindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit workingwindow(QWidget *parent = 0);
    ~workingwindow();

    QImage ColorWheel;

    bool colorSampler;

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

    void on_EraserButton_toggled(bool checked);

    void on_BrushButton_toggled(bool checked);

    void on_TextButton_toggled(bool checked);

    void mousePressEvent(QMouseEvent *event);

    void mouseMoveEvent(QMouseEvent *event);

    void mouseReleaseEvent(QMouseEvent *event);

    void drawLine(QPoint &lastpoint);

    void on_Redo_clicked();

    void on_Negative_clicked();

    void on_OpenNew_clicked();

    void on_lineEdit_returnPressed();

    void on_lineEdit_textEdited(const QString &arg1);

    void on_horizontalSlider_valueChanged(int value);

    void on_colorSample_toggled(bool checked);

private:
    Ui::workingwindow *ui;
};

#endif // WORKINGWINDOW_H
