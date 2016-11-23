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

    if (f != Face::NONE) {
        ui->rasterWidget->setImage(ui->display->getImage());
    }
}


void CubeMapEditor::on_pushButton_loadImage_clicked()
{
    QString imagePath = QFileDialog::getOpenFileName( this, "Open File", "", "JPEG (*.jpg *.jpeg);;PNG (*.png)" );

    QImage image;
    image.load(imagePath);
    ui->display->loadImage(image);
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

void CubeMapEditor::on_pushButton_saveCube_clicked()
{
    QSize sz = size();

    QString filenames[] = {
        "tmp/Left",
        "tmp/Top",
        "tmp/Front",
        "tmp/Bottom",
        "tmp/Right",
        "tmp/Back"
    };
    if (!QDir("tmp/").exists())
        QDir("tmp/").mkdir(".");

    for (Face f = Face::Left; f < Face::NONE; f=(Face)(f+1)) {
        ui->rasterWidget->setImage(ui->display->getImage(f));
        ui->rasterWidget->raster(filenames[f]+".jpg");
    }

    setFixedSize(sz);
}
