#ifndef MODELWINDOW_H
#define MODELWINDOW_H

#include <QDialog>
#include "ImportedImage.h"
#include "modeleditor.h"
namespace Ui {
class ModelWindow;
}

class ModelWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ModelWindow(QWidget *parent = 0);
    ~ModelWindow();

    void createModel(box b,int density_split,int loop_dist,float bg_bias);
    void exportModel(box b,int density_split,int loop_dist,float bg_bias, string path);
private slots:
    void on_openGLWidget_resized();

    void on_ModelWindow_accepted();


    void on_openGLWidget_destroyed();

private:

    Ui::ModelWindow *ui;
};

#endif // MODELWINDOW_H
