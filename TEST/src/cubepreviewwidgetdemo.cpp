#include "cubepreviewwidgetdemo.h"
#include "ui_cubepreviewwidgetdemo.h"

CubePreviewWidgetDemo::CubePreviewWidgetDemo(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CubePreviewWidgetDemo)
{
    ui->setupUi(this);

    connect(ui->zoom,  SIGNAL(valueChanged(int)), this, SLOT(zoom_valueChanged(int)));
    connect(ui->tiltX, SIGNAL(valueChanged(int)), this, SLOT(tilt_x_valueChanged(int)));
    connect(ui->tiltY, SIGNAL(valueChanged(int)), this, SLOT(tilt_y_valueChanged(int)));
    connect(ui->tiltZ, SIGNAL(valueChanged(int)), this, SLOT(tilt_z_valueChanged(int)));
}

CubePreviewWidgetDemo::~CubePreviewWidgetDemo()
{
    delete ui;
}

void CubePreviewWidgetDemo::zoom_valueChanged(int value)
{
    double zoom = (double)value/(double)(ui->zoom->maximum());
    ui->previewWidget->setZoom(zoom);
}

void CubePreviewWidgetDemo::tilt_x_valueChanged(int value)
{
    double amt = (double)value/(double)(ui->tiltX->maximum());
    ui->previewWidget->setTilt_x(amt);
}

void CubePreviewWidgetDemo::tilt_y_valueChanged(int value)
{
    double amt = (double)value/(double)(ui->tiltY->maximum());
    ui->previewWidget->setTilt_y(amt);
}

void CubePreviewWidgetDemo::tilt_z_valueChanged(int value)
{
    double amt = (double)value/(double)(ui->tiltZ->maximum());
    ui->previewWidget->setTilt_z(amt);
}
