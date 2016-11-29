#ifndef CUBEMAPEDITORIMAGE_DRIVER_H
#define CUBEMAPEDITORIMAGE_DRIVER_H

#include <QDialog>

#include "../src/cubemapeditorimage.h"

namespace Ui {
class CubeMapEditorImage_Driver;
}


class CubeMapEditorImage_Driver : public QDialog
{
    Q_OBJECT

public:

    explicit CubeMapEditorImage_Driver(QWidget* parent=0);
    ~CubeMapEditorImage_Driver();
    bool test_path(CubeMapEditorImage* image);
    bool test_tmpPath(CubeMapEditorImage* image);
    bool test_haveImage(CubeMapEditorImage* image);
    bool test_image(CubeMapEditorImage* image);
    bool test_focus(CubeMapEditorImage* image);
    bool test_rotation(CubeMapEditorImage* image);
    void execute();
private slots:
    void on_pushButton_clicked();

private:
    QString boolToStatus(bool b);

    Ui::CubeMapEditorImage_Driver *ui;
};

#endif // CUBEMAPEDITORIMAGE_DRIVER_H
