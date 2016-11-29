#ifndef CUBEMAPEDITORRASTERWIDGET_DRIVER_H
#define CUBEMAPEDITORRASTERWIDGET_DRIVER_H

#include <QDialog>

namespace Ui {
class CubeMapEditorRasterWidget_Driver;
}

class CubeMapEditorRasterWidget_Driver : public QDialog
{
    Q_OBJECT

public:
    explicit CubeMapEditorRasterWidget_Driver(QWidget *parent = 0);
    ~CubeMapEditorRasterWidget_Driver();

    bool test_raster();

    void execute();
private slots:
    void on_pushButton_clicked();

private:
    Ui::CubeMapEditorRasterWidget_Driver *ui;
    QString boolToStatus(bool b);
};

#endif // CUBEMAPEDITORRASTERWIDGET_DRIVER_H
