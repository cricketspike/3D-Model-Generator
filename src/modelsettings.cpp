#include "modelsettings.h"
#include "ui_modelsettings.h"
#include"modelwindow.h"
#include<QFileDialog>

ModelSettings::ModelSettings(QWidget *parent) :
    QDialog(parent),m_res_split(5),m_loop_dis(5),m_background_bias(10),ui(new Ui::ModelSettings)
{
    ui->setupUi(this);
}

ModelSettings::~ModelSettings()
{
    delete ui;
}

void ModelSettings::on_pushButton_2_clicked()//preview
{
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
    ModelWindow mwin;
    mwin.setModal(true);
    mwin.createModel(b,m_res_split,m_loop_dis,m_background_bias);
    mwin.exec();
}

void ModelSettings::on_resolution_splitting_valueChanged(int arg1)
{
    m_res_split=arg1;

}


void ModelSettings::on_Level_dist_valueChanged(int arg1)
{
    m_loop_dis=arg1;
}


void ModelSettings::on_bg_bias_spinner_valueChanged(double arg1)
{
    m_background_bias=arg1;
}


void ModelSettings::on_pushButton_clicked()//export
{

    m_export_path= QFileDialog::getSaveFileName().toStdString();
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
    ModelWindow mwin;
    mwin.setModal(true);
    mwin.exportModel(b,m_res_split,m_loop_dis,m_background_bias, m_export_path);

    mwin.exec();
}

