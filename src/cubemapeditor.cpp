#include <iostream>
#include <QSignalMapper>
#include <QFileDialog>
#include "cubemapeditor.h"
#include "ui_cubemapeditor.h"


CubeMapEditor::CubeMapEditor(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CubeMapEditor)
{
    ui->setupUi(this);

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
    ui->pushButton_weight->setEnabled(f != Face::NONE);
}


void CubeMapEditor::on_pushButton_loadImage_clicked()
{
    QString imagePath = QFileDialog::getOpenFileName( this, "Open File", "", "JPEG (*.jpg *.jpeg);;PNG (*.png)" );

    image.load(imagePath);
    ui->display->loadImage(image);
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

