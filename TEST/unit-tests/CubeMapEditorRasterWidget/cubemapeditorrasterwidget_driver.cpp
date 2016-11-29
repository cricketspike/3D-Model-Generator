#include <QFile>
#include "src/cubemapeditorimage.h"
#include "src/cubemapeditorrasterwidget.h"
#include "cubemapeditorrasterwidget_driver.h"
#include "ui_cubemapeditorrasterwidget_driver.h"

CubeMapEditorRasterWidget_Driver::CubeMapEditorRasterWidget_Driver(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CubeMapEditorRasterWidget_Driver)
{
    ui->setupUi(this);
    ui->rasterWidget->setVisible(false);
}

CubeMapEditorRasterWidget_Driver::~CubeMapEditorRasterWidget_Driver()
{
    delete ui;
}

bool CubeMapEditorRasterWidget_Driver::test_raster()
{
    QImage images[] = {
        QImage(":/images/image0.jpg"),
        QImage(":/images/image1.jpg"),
        QImage(":/images/image2.jpg"),
        QImage(":/images/image3.jpg"),
        QImage(":/images/image4.jpg"),
        QImage(":/images/image5.jpg")
    };
    QString paths_out[] = {
        "out0.jpg",
        "out1.jpg",
        "out2.jpg",
        "out3.jpg",
        "out4.jpg",
        "out5.jpg",
    };

    for (int i=0; i<6; i++) {
        ui->rasterWidget->setVisible(true);
        CubeMapEditorImage* img = new CubeMapEditorImage();
        ui->rasterWidget->makeCurrent();
        img->setImage(images[i]);
        ui->rasterWidget->doneCurrent();

        ui->rasterWidget->setImage(img);
        ui->rasterWidget->raster(paths_out[i]);

        delete img;
    }

    bool ret = true;

    for (int i=0; i<6; i++) {
        QFile f(paths_out[i]);
        if (!f.exists()) {
            ret = false;
            break;
        } else {
            f.deleteLater();
        }
    }

    return ret;
}

void CubeMapEditorRasterWidget_Driver::execute()
{
    // Setup

    // Excercise & Verify
    ui->textEdit->setText(ui->textEdit->toPlainText()+"test_raster: "     +boolToStatus(test_raster()));

    ui->textEdit->setText(ui->textEdit->toPlainText()+"done.");

    // Teardown
}

void CubeMapEditorRasterWidget_Driver::on_pushButton_clicked()
{
    execute();
}

QString CubeMapEditorRasterWidget_Driver::boolToStatus(bool b)
{
    return b ? "success\n" : "failure\n";
}
