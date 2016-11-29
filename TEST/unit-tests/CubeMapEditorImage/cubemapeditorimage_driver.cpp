#include <iostream>

#include "cubemapeditorimage_driver.h"
#include "ui_cubemapeditorimage_driver.h"

CubeMapEditorImage_Driver::CubeMapEditorImage_Driver(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CubeMapEditorImage_Driver)
{
    ui->setupUi(this);
}

CubeMapEditorImage_Driver::~CubeMapEditorImage_Driver()
{
    delete ui;
}

bool CubeMapEditorImage_Driver::test_path(CubeMapEditorImage* image)
{
    QString test_path = "ABCD";
    QString test_path_empty;

    image->setPath(test_path);
    bool test1 = (test_path == image->getPath());

    image->setPath(test_path_empty);
    bool test2 = (test_path_empty == image->getPath());

    return test1 && test2;
}

bool CubeMapEditorImage_Driver::test_tmpPath(CubeMapEditorImage* image)
{
    QString test_path = "ABCD";
    QString test_path_empty;

    image->setTmpPath(test_path);
    bool test1 = (test_path == image->getTmpPath());

    image->setTmpPath(test_path_empty);
    bool test2 = (test_path_empty == image->getTmpPath());

    return test1 && test2;
}

bool CubeMapEditorImage_Driver::test_haveImage(CubeMapEditorImage* image)
{
    QImage test_image(":/images/image0.jpg");

    bool test1 = (image->haveImage() == false);

    image->setImage(test_image);

    bool test2 = (image->haveImage() == true);

    return test1 && test2;
}

bool CubeMapEditorImage_Driver::test_image(CubeMapEditorImage* image)
{
    QImage test_image(":/images/image0.jpg");
    QImage test_image_empty;

    image->setImage(test_image);
    bool test1 = (test_image == image->getImage());

    image->setImage(test_image_empty);
    bool test2 = (test_image_empty == image->getImage());

    return test1 && test2;
}

bool CubeMapEditorImage_Driver::test_focus(CubeMapEditorImage* image)
{
    double zoom = 0.7;
    QPointF offset(-1, -2);

    image->setFocus(zoom, offset);

    double zoom_out;
    QPointF offset_out;

    image->getFocus(zoom_out, offset_out);

    return (zoom == zoom_out && offset == offset_out);
}

bool CubeMapEditorImage_Driver::test_rotation(CubeMapEditorImage* image)
{
    bool test1 = image->getRotation() == 0;

    image->rotate();
    bool test2 = image->getRotation() == 1;

    image->rotate();
    bool test3 = image->getRotation() == 2;

    image->rotate();
    bool test4 = image->getRotation() == 3;

    image->rotate();
    bool test5 = image->getRotation() == 0;

    return test1 && test2 && test3 && test4 && test5;
}

void CubeMapEditorImage_Driver::execute()
{
    // Setup
    CubeMapEditorImage* image = new CubeMapEditorImage();

    // Excercise & Verify
    ui->textEdit->setText(ui->textEdit->toPlainText()+"test_path: "     +boolToStatus(test_path(image)));
    ui->textEdit->setText(ui->textEdit->toPlainText()+"test_tmpPath: "  +boolToStatus(test_tmpPath(image)));
    ui->textEdit->setText(ui->textEdit->toPlainText()+"test_haveImage: "+boolToStatus(test_haveImage(image)));
    ui->textEdit->setText(ui->textEdit->toPlainText()+"test_image: "    +boolToStatus(test_image(image)));
    ui->textEdit->setText(ui->textEdit->toPlainText()+"test_focus: "    +boolToStatus(test_focus(image)));
    ui->textEdit->setText(ui->textEdit->toPlainText()+"test_rotation: " +boolToStatus(test_rotation(image)));

    ui->textEdit->setText(ui->textEdit->toPlainText()+"done.");

    // Teardown
    delete image;
}

void CubeMapEditorImage_Driver::on_pushButton_clicked()
{
    execute();
}

QString CubeMapEditorImage_Driver::boolToStatus(bool b)
{
    return b ? "success\n" : "failure\n";
}
