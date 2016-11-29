#include "cubemapeditordisplay_driver.h"
#include "ui_cubemapeditordisplay_driver.h"

CubeMapEditorDisplay_Driver::CubeMapEditorDisplay_Driver(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CubeMapEditorDisplay_Driver)
{
    ui->setupUi(this);
}

CubeMapEditorDisplay_Driver::~CubeMapEditorDisplay_Driver()
{
    delete ui;
}

bool CubeMapEditorDisplay_Driver::test_haveImage()
{
    QString paths[] = {
        ":/images/image0.jpg",
        ":/images/image1.jpg",
        ":/images/image2.jpg",
        ":/images/image3.jpg",
        ":/images/image4.jpg",
        ":/images/image5.jpg"
    };

    bool ret = true;

    for (int i=0; i<6; i++) {
        ui->display->selectFace((CubeMapEditor::Face)i);


        bool test1 = (ui->display->haveImage() == false);

        ui->display->loadImage(QImage(paths[i]));

        bool test2 = (ui->display->haveImage() == true);

        if (!(test1 && test2)) {
            ret = false;
            break;
        }
    }

    return ret;
}

bool CubeMapEditorDisplay_Driver::test_image()
{
    QImage images[] = {
        QImage(":/images/image0.jpg"),
        QImage(":/images/image1.jpg"),
        QImage(":/images/image2.jpg"),
        QImage(":/images/image3.jpg"),
        QImage(":/images/image4.jpg"),
        QImage(":/images/image5.jpg")
    };
    QImage image_empty;

    bool ret = true;

    for (int i=0; i<6; i++) {
        ui->display->selectFace((CubeMapEditor::Face)i);

        ui->display->getImage()->setImage(images[i]);
        bool test1 = (images[i] == ui->display->getImage()->getImage());

        ui->display->getImage()->setImage(image_empty);
        bool test2 = (image_empty == ui->display->getImage()->getImage());

        if (!(test1 && test2)) {
            ret = false;
            break;
        }
    }

    return ret;
}

bool CubeMapEditorDisplay_Driver::test_focus()
{
    double zoom = 0.7;
    QPointF offset(-1, -2);

    bool ret = true;

    for (int i=0; i<6; i++) {
        ui->display->selectFace((CubeMapEditor::Face)i);

        ui->display->getImage()->setFocus(zoom, offset);

        double zoom_out;
        QPointF offset_out;

        ui->display->getImage()->getFocus(zoom_out, offset_out);

        if (!(zoom == zoom_out && offset == offset_out)) {
            ret = false;
            break;
        }
    }

    return ret;
}

void CubeMapEditorDisplay_Driver::execute()
{
    // Setup

    // Excercise & Verify
    ui->textEdit->setText(ui->textEdit->toPlainText()+"test_haveImage: "     +boolToStatus(test_haveImage()));
    ui->textEdit->setText(ui->textEdit->toPlainText()+"test_image: "         +boolToStatus(test_image()));
    ui->textEdit->setText(ui->textEdit->toPlainText()+"test_focus: "         +boolToStatus(test_focus()));

    ui->textEdit->setText(ui->textEdit->toPlainText()+"done.");

    // Teardown
}

QString CubeMapEditorDisplay_Driver::boolToStatus(bool b)
{
    return b ? "success\n" : "failure\n";
}

void CubeMapEditorDisplay_Driver::on_pushButton_clicked()
{
    execute();
}
