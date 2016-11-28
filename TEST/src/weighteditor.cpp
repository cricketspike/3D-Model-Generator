#include "weighteditor.h"
#include "ui_weighteditor.h"
#include "iostream"
#include <QMouseEvent>
#include <QFileDialog>


weighteditor::weighteditor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::weighteditor){
    ui->setupUi(this);

    //QImage img( ":/images/image5.jpg" );

    QString path = QFileDialog::getOpenFileName( this, "Open File", "", "JPEG (*.jpg *.jpeg);;PNG (*.png)" );




        //std::cout<<"TEST1";
        //std::string a;
        //std::cin>>a;
        //cubemapeditor
    QImage img;
   //std:: cout<<"TEST2";
   //std::cin>>a;
    //std::cout<<"test4";

    img.load(path);
/*
    weight = std::vector<std::vector<uint8_t>>();

    //Go through every pixel in the picture
    for ( int col = 0; col < img.width(); ++col ) {

      weight.push_back(std::vector<uint8_t>());
      for ( int row = 0; row < img.height(); ++row ) {
        uint8_t data = 0;
        weight[col].push_back(data);
      }
    }
*/
    this->setMinimumSize(img.width(),img.height());
    this->setMaximumSize(img.width(),img.height());
    //std::cout<<"TEST3"<<std::endl;
    //img->fill(Qt::red);
    ui->label_image->setPixmap
            (QPixmap::fromImage(img).scaled
            (img.width(),img.height(),Qt::KeepAspectRatio));
    ui->label_image->adjustSize();

}

weighteditor::~weighteditor()
{
    delete ui;
}

void weighteditor::mousePressEvent(QMouseEvent* event)
{
    double x = ((double)event->pos().x());
    double y = ((double)event->pos().y());
    if (event->buttons() == Qt::LeftButton) {
        image->addWeight(x,y);
    }
    if (event->buttons() == Qt::RightButton) {
        image->subtractWeight(x,y);
    }
}

void weighteditor::closeEvent(QCloseEvent *event) {
    std::cout<<"Check"<<std::endl;
    QWidget::closeEvent(event);
}


