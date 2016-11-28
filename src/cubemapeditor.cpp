#include <iostream>
#include <QSignalMapper>
#include <QFileDialog>
#include "cubemapeditor.h"
#include "cubemapeditordisplay.h"
#include "ui_cubemapeditor.h"
#include "modelwindow.h"
#include "src/weighteditor.h"
#include "modelsettings.h"

CubeMapEditor::CubeMapEditor(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CubeMapEditor)
{
    ui->setupUi(this);
    ui->rasterWidget->setVisible(false);
    ui->rasterWidget->setImage(ui->display->getImage());

    connect(ui->horizontalSlider_cubePreview_zoom,  SIGNAL(valueChanged(int)), this, SLOT(zoom_valueChanged(int)));
    connect(ui->dial_cubePreview_tx, SIGNAL(valueChanged(int)), this, SLOT(tilt_x_valueChanged(int)));
    connect(ui->dial_cubePreview_ty, SIGNAL(valueChanged(int)), this, SLOT(tilt_y_valueChanged(int)));
    connect(ui->dial_cubePreview_tz, SIGNAL(valueChanged(int)), this, SLOT(tilt_z_valueChanged(int)));

    /* Connect the clicked() signal of each selection button
    *    to the selection(int) slot, with paramter based on
    *    the signal emitter
    *
    */

    QSignalMapper* signalMapper = new QSignalMapper(this);
    connect(ui->pushButton_front, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->pushButton_right, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->pushButton_back, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->pushButton_left, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->pushButton_top, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->pushButton_bottom, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->pushButton_background, SIGNAL(clicked()), signalMapper, SLOT(map()));

    signalMapper->setMapping(ui->pushButton_front, Face::Front);
    signalMapper->setMapping(ui->pushButton_right, Face::Right);
    signalMapper->setMapping(ui->pushButton_back, Face::Back);
    signalMapper->setMapping(ui->pushButton_left, Face::Left);
    signalMapper->setMapping(ui->pushButton_top, Face::Top);
    signalMapper->setMapping(ui->pushButton_bottom, Face::Bottom);
    signalMapper->setMapping(ui->pushButton_background, Face::NONE);
    connect(signalMapper, SIGNAL(mapped(int)), this, SLOT(selection(int)));
}

CubeMapEditor::~CubeMapEditor()
{
    delete ui;
}

void CubeMapEditor::selection(int selection)
{
    Face f = (Face)selection;
    this->ui->display->selectFace(f);

    // Can't load an image when no face is selected
    ui->pushButton_loadImage->setEnabled(f != Face::NONE);
    ui->pushButton_weight->setEnabled(ui->display->haveImage(f));

    if (f != Face::NONE) {
        ui->rasterWidget->setImage(ui->display->getImage());
    }
}


void CubeMapEditor::on_pushButton_loadImage_clicked()
{
    QString imagePath = QFileDialog::getOpenFileName( this, "Open File", "", "JPEG (*.jpg *.jpeg);;PNG (*.png)" );

    if (imagePath.isEmpty())
        return;

    QImage image;
    image.load(imagePath);
    ui->display->loadImage(image);
    ui->pushButton_weight->setEnabled(true);
    ui->pushButton_cubePreviewUpdate->setEnabled(allHaveImage());
}

void CubeMapEditor::on_pushButton_clicked()
{
    ModelSettings settings_window;
    settings_window.setModal(true);
    settings_window.exec();

}

void CubeMapEditor::on_comboBox_projection_currentIndexChanged(int index)
{
    CubeMapEditorDisplay::ProjectionMode mode = (CubeMapEditorDisplay::ProjectionMode)index;

    ui->display->setProjectionMode(mode);
}

void CubeMapEditor::on_pushButton_weight_clicked()
{
    weighteditor weight;
    weight.setModal(true);
    weight.loadImage(ui->display->getImage());
    weight.exec();
    //weight = new weighteditor();
    //weight->loadImage(ui->display->getImage());
    //weight->show();

}


bool CubeMapEditor::allHaveImage(){
    for (Face f = Face::Left; f < Face::NONE; f=(Face)(f+1)) {
        if (ui->display->haveImage(f) == false) return false;
    }
    return true;
}



void CubeMapEditor::zoom_valueChanged(int value)
{
    double zoom = (double)value/(double)(ui->horizontalSlider_cubePreview_zoom->maximum());
    ui->cubePreviewWidget->setZoom(zoom);
}

void CubeMapEditor::tilt_x_valueChanged(int value)
{
    double amt = (double)value/(double)(ui->dial_cubePreview_tx->maximum());
    ui->cubePreviewWidget->setTilt_x(amt);
}

void CubeMapEditor::tilt_y_valueChanged(int value)
{
    double amt = (double)value/(double)(ui->dial_cubePreview_ty->maximum());
    ui->cubePreviewWidget->setTilt_y(amt);
}

void CubeMapEditor::tilt_z_valueChanged(int value)
{
    double amt = (double)value/(double)(ui->dial_cubePreview_tz->maximum());
    ui->cubePreviewWidget->setTilt_z(amt);
}

void CubeMapEditor::on_pushButton_cubePreviewUpdate_clicked()
{
    QSize sz = size();

    QString filenames[] = {
        "tmp/Left.jpg",
        "tmp/Top.jpg",
        "tmp/Front.jpg",
        "tmp/Bottom.jpg",
        "tmp/Right.jpg",
        "tmp/Back.jpg"

    };
    if (!QDir("tmp/").exists())
        QDir("tmp/").mkdir(".");

    for (Face f = Face::Left; f < Face::NONE; f=(Face)(f+1)) {
        ui->rasterWidget->setImage(ui->display->getImage(f));
        ui->rasterWidget->raster(filenames[f]);
    }

    QImage img0( "tmp/Left.jpg" );
    QImage img1( "tmp/Front.jpg" );
    QImage img2( "tmp/Right.jpg" );
    QImage img3( "tmp/Back.jpg" );
    QImage img4( "tmp/Top.jpg" );
    QImage img5( "tmp/Bottom.jpg" );

    vector<QImage> images;
    images.push_back(img0);
    images.push_back(img1);
    images.push_back(img2);
    images.push_back(img3);
    images.push_back(img4);
    images.push_back(img5);

    box b = box(images);
    ui->cubePreviewWidget->texturesFromBox(b);

    setFixedSize(sz);
    ui->pushButton->setEnabled(allHaveImage());
}
