#include "importwindow.h"
#include "ui_importwindow.h"

#include <vector>
#include "src/ImportedImage.h"

importwindow::importwindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::importwindow)
{
    ui->setupUi(this);

    QImage img0( ":/images/image0.jpg" );
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


}

importwindow::~importwindow()
{
    delete ui;
}
