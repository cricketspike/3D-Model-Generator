#ifndef CUBEMAPEDITORDISPLAY_DRIVER_H
#define CUBEMAPEDITORDISPLAY_DRIVER_H

#include <QDialog>

#include "../src/cubemapeditorimage.h"

namespace Ui {
class CubeMapEditorDisplay_Driver;
}

class CubeMapEditorDisplay_Driver : public QDialog
{
    Q_OBJECT

public:
    explicit CubeMapEditorDisplay_Driver(QWidget *parent = 0);
    ~CubeMapEditorDisplay_Driver();

    bool test_haveImage();
    bool test_image();
    bool test_focus();

    void execute();
private slots:
    void on_pushButton_clicked();

private:
    Ui::CubeMapEditorDisplay_Driver *ui;
    QString boolToStatus(bool b);
};

#endif // CUBEMAPEDITORDISPLAY_DRIVER_H
