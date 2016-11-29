#include <QTime>
#include "cubepreviewwidget_driver.h"
#include "ui_cubepreviewwidget_driver.h"

CubePreviewWidget_Driver::CubePreviewWidget_Driver(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CubePreviewWidget_Driver)
{
    ui->setupUi(this);
}

CubePreviewWidget_Driver::~CubePreviewWidget_Driver()
{
    delete ui;
}

void CubePreviewWidget_Driver::test_textureFromBox()
{
    QImage images[] = {
        QImage(":/images/image4.jpg"),
        QImage(":/images/image1.jpg"),
        QImage(":/images/image0.jpg"),
        QImage(":/images/image3.jpg"),
        QImage(":/images/image5.jpg"),
        QImage(":/images/image2.jpg")
    };

    ImportedImage importedImages[] = {
        ImportedImage(),
        ImportedImage(),
        ImportedImage(),
        ImportedImage(),
        ImportedImage(),
        ImportedImage()
    };

    box b;
    for (int i=0; i<6; i++) {
        importedImages[i].setPic(images[i]);
        b.addSide(importedImages[i]);
    }

    ui->cubePreviewWidget->texturesFromBox(b);
}

bool CubePreviewWidget_Driver::test_useTexture()
{
    ui->cubePreviewWidget->setUseTexture(false);
    bool useTexture1 = ui->cubePreviewWidget->getUseTexture();

    ui->cubePreviewWidget->setUseTexture(true);
    bool useTexture2 = ui->cubePreviewWidget->getUseTexture();

    return (!useTexture1 && useTexture2);
}

void delay(int n)
{
    QTime dieTime= QTime::currentTime().addSecs(n);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}
void CubePreviewWidget_Driver::test_setZoom()
{
    ui->cubePreviewWidget->setZoom(0.5);
}

void CubePreviewWidget_Driver::test_setTilt_x()
{
    test_setTilt_x_neg();
    delay(1);
    test_setTilt_x_zro();
    delay(1);
    test_setTilt_x_pos();
    delay(1);
    test_setTilt_x_zro();
    delay(1);
}
void CubePreviewWidget_Driver::test_setTilt_y()
{
    test_setTilt_y_neg();
    delay(1);
    test_setTilt_y_zro();
    delay(1);
    test_setTilt_y_pos();
    delay(1);
    test_setTilt_y_zro();
    delay(1);
}
void CubePreviewWidget_Driver::test_setTilt_z()
{
    test_setTilt_z_neg();
    delay(1);
    test_setTilt_z_zro();
    delay(1);
    test_setTilt_z_pos();
    delay(1);
    test_setTilt_z_zro();
    delay(1);
}

void CubePreviewWidget_Driver::execute()
{
    // Setup

    // Excercise & Verify
    ui->textEdit->setText(ui->textEdit->toPlainText()+"test_textureFromBox...\n");
    test_textureFromBox();

    ui->textEdit->setText(ui->textEdit->toPlainText()+"test_useTexture: "+boolToStatus(test_useTexture()));

    ui->textEdit->setText(ui->textEdit->toPlainText()+"test_setZoom...\n");
    test_setZoom();


    ui->textEdit->setText(ui->textEdit->toPlainText()+"test_setTilt_x...\n");
    test_setTilt_x();
    ui->textEdit->setText(ui->textEdit->toPlainText()+"test_setTilt_y...\n");
    test_setTilt_y();
    ui->textEdit->setText(ui->textEdit->toPlainText()+"test_setTilt_z...\n");
    test_setTilt_z();

    ui->textEdit->setText(ui->textEdit->toPlainText()+"done.");

    // Teardown
}

QString CubePreviewWidget_Driver::boolToStatus(bool b)
{
    return b ? "success\n" : "failure\n";
}

void CubePreviewWidget_Driver::test_setTilt_x_neg()
{
    ui->cubePreviewWidget->setTilt_x(-0.125);
}
void CubePreviewWidget_Driver::test_setTilt_x_zro()
{
    ui->cubePreviewWidget->setTilt_x(0.0);
}

void CubePreviewWidget_Driver::test_setTilt_x_pos()
{
    ui->cubePreviewWidget->setTilt_x(0.125);
}
void CubePreviewWidget_Driver::test_setTilt_y_neg()
{
    ui->cubePreviewWidget->setTilt_y(-0.125);
}
void CubePreviewWidget_Driver::test_setTilt_y_zro()
{
    ui->cubePreviewWidget->setTilt_y(0.0);
}

void CubePreviewWidget_Driver::test_setTilt_y_pos()
{
    ui->cubePreviewWidget->setTilt_y(0.125);
}

void CubePreviewWidget_Driver::test_setTilt_z_neg()
{
    ui->cubePreviewWidget->setTilt_z(-0.125);
}
void CubePreviewWidget_Driver::test_setTilt_z_zro()
{
    ui->cubePreviewWidget->setTilt_z(0.0);
}

void CubePreviewWidget_Driver::test_setTilt_z_pos()
{
    ui->cubePreviewWidget->setTilt_z(0.125);
}

void CubePreviewWidget_Driver::on_pushButton_clicked()
{
    execute();
}
