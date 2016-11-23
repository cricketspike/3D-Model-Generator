#include "modelsettings.h"
#include "ui_modelsettings.h"
#include"modelwindow.h"

ModelSettings::ModelSettings(QWidget *parent) :
    QDialog(parent),m_res_split(5),m_loop_dis(5),ui(new Ui::ModelSettings)
{
    ui->setupUi(this);
}

ModelSettings::~ModelSettings()
{
    delete ui;
}

void ModelSettings::on_pushButton_2_clicked()//preview
{
    QImage img0(":/images/image0.jpg" );
    QImage img1( ":/images/image1.jpg" );
    QImage img2( ":/images/image2.jpg" );
    QImage img3( ":/images/image3.jpg" );
    QImage img4( ":/images/image4.jpg" );
    QImage img5( ":/images/image5.jpg" );

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
    mwin.createModel(b,m_res_split,m_loop_dis);

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

void ModelSettings::on_pushButton_clicked()//export
{
    QImage img0(":/images/image0.jpg" );
    QImage img1( ":/images/image1.jpg" );
    QImage img2( ":/images/image2.jpg" );
    QImage img3( ":/images/image3.jpg" );
    QImage img4( ":/images/image4.jpg" );
    QImage img5( ":/images/image5.jpg" );

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
    mwin.createModel(b,m_res_split,m_loop_dis);

    mwin.exec();
}
