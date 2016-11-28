#ifndef CUBEPREVIEWWIDGETDEMO_H
#define CUBEPREVIEWWIDGETDEMO_H

#include <QMainWindow>

namespace Ui {
class CubePreviewWidgetDemo;
}

class CubePreviewWidgetDemo : public QMainWindow
{
    Q_OBJECT

public:
    explicit CubePreviewWidgetDemo(QWidget *parent = 0);
    ~CubePreviewWidgetDemo();

private:
    Ui::CubePreviewWidgetDemo *ui;

private slots:
    void zoom_valueChanged(int value);
    void tilt_x_valueChanged(int value);
    void tilt_y_valueChanged(int value);
    void tilt_z_valueChanged(int value);
};

#endif // CUBEPREVIEWWIDGETDEMO_H
