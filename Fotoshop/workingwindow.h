/*! \header Working Window
 *          \brief Header file for the window that opens the image and the work area */

#ifndef WORKINGWINDOW_H
#define WORKINGWINDOW_H

#include "includes.h"

extern undoArr *undofunc; //! \var undoArr *undofunc \brief creates a new type of the undo class

extern std::vector<QImage> undoVector;

extern double myInputSize; //! \var double myInputSize \brief size parameter for the resize tool

namespace Ui {
class workingwindow;
}

class workingwindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit workingwindow(QWidget *parent = 0);
    ~workingwindow();

    QImage ColorWheel; //! \image QImage ColorWheel \brief colorWheel for reference in the UI

    bool colorSampler; //! \var bool ColorSampler \brief tool to keep track of whether the sampler tool is active

    double colorFactor; //! \var double colorFacotor \brief tool to translate percent values into rgb values between 1 - 255

    QColor customColor; //! \var QColor cusotmColor \brief stores the custom rgb values for use with the pen

    QImage colorPreview; //! \image QImage colorPreview \brief a window to display the current color selection

    bool bucket; //! \var bool bucket \brief keep track of whether the bucket has been selected

    QPoint StaticXY, StaticXY2; //! \var StaticXY \var StaticXY2 \brief QPoint holding a value for a simple line tool.

    double leftLinePos, rightLinePos, topLinePos, bottomLinePos;

private slots:

    //! slots to keep track of all of the buttons that are checked or clicked in the work area
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

    void on_redSlider_valueChanged(int value);

    void on_greenSlider_valueChanged(int value);

    void on_blueSlider_valueChanged(int value);

    void on_bucket_toggled(bool checked);

    void on_CropFromLeft_valueChanged(int value);

    void on_CropFromRight_valueChanged(int value);

    void on_CropFromTop_valueChanged(int value);

    void on_CropFromDown_valueChanged(int value);

private:
    Ui::workingwindow *ui;
};

#endif // WORKINGWINDOW_H
