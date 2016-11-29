#ifndef CUBEPREVIEWWIDGET_DRIVER_H
#define CUBEPREVIEWWIDGET_DRIVER_H

#include <QDialog>

namespace Ui {
class CubePreviewWidget_Driver;
}

class CubePreviewWidget_Driver : public QDialog
{
    Q_OBJECT

public:
    explicit CubePreviewWidget_Driver(QWidget *parent = 0);
    ~CubePreviewWidget_Driver();

    void test_textureFromBox();
    bool test_useTexture();
    void test_setZoom();
    void test_setTilt_x();
    void test_setTilt_y();
    void test_setTilt_z();

    void execute();

private slots:
    void test_setTilt_z_pos();
    void test_setTilt_z_zro();
    void test_setTilt_z_neg();

    void test_setTilt_y_pos();
    void test_setTilt_y_zro();
    void test_setTilt_y_neg();

    void test_setTilt_x_pos();
    void test_setTilt_x_zro();
    void test_setTilt_x_neg();
    void on_pushButton_clicked();

private:
    Ui::CubePreviewWidget_Driver *ui;
    QString boolToStatus(bool b);
};

#endif // CUBEPREVIEWWIDGET_DRIVER_H
