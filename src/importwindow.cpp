#include "importwindow.h"
#include "ui_importwindow.h"

#include <vector>
#include <qfiledialog.h>
#include <src/ImportedImage.h>
#include <QMessageBox>

importwindow::importwindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::importwindow) {

  ui->setupUi(this);

  //uplaod temp images
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

  cube = box(images);


  //Set temp images and keep images scaled
  ui->label->setPixmap(QPixmap::fromImage(cube.getSides().at(0).getImage()));
  ui->label->setScaledContents(true);
  ui->label_2->setPixmap(QPixmap::fromImage(cube.getSides().at(1).getImage()));
  ui->label_2->setScaledContents(true);
  ui->label_3->setPixmap(QPixmap::fromImage(cube.getSides().at(2).getImage()));
  ui->label_3->setScaledContents(true);
  ui->label_4->setPixmap(QPixmap::fromImage(cube.getSides().at(3).getImage()));
  ui->label_4->setScaledContents(true);
  ui->label_5->setPixmap(QPixmap::fromImage(cube.getSides().at(4).getImage()));
  ui->label_5->setScaledContents(true);
  ui->label_6->setPixmap(QPixmap::fromImage(cube.getSides().at(5).getImage()));
  ui->label_6->setScaledContents(true);
}

importwindow::~importwindow(){
  delete ui;
}

void importwindow::on_importimage1_clicked() {
  QString filename = QFileDialog::getOpenFileName(this,tr("Open File"), "C://", "JPG (*.jpg)");
  QImage newImage (filename);
  cube.setSide(0,ImportedImage(newImage));
  cube.setPixelsAt(0);
  ui->label->setPixmap(QPixmap::fromImage(cube.getSides().at(0).getImage()));
}

void importwindow::on_importimage2_clicked() {
  QString filename = QFileDialog::getOpenFileName(this,tr("Open File"), "C://", "JPG (*.jpg)");
  QImage newImage (filename);
  cube.setSide(1,ImportedImage(newImage));
  cube.setPixelsAt(1);
  ui->label_2->setPixmap(QPixmap::fromImage(cube.getSides().at(1).getImage()));
}

void importwindow::on_importimage3_clicked() {
  QString filename = QFileDialog::getOpenFileName(this,tr("Open File"), "C://", "JPG (*.jpg)");
  QImage newImage (filename);
  cube.setSide(2,ImportedImage(newImage));
  cube.setPixelsAt(2);
  ui->label_3->setPixmap(QPixmap::fromImage(cube.getSides().at(2).getImage()));
}

void importwindow::on_importimage4_clicked() {
  QString filename = QFileDialog::getOpenFileName(this,tr("Open File"), "C://", "JPG (*.jpg)");
  QImage newImage (filename);
  cube.setSide(3,ImportedImage(newImage));
  cube.setPixelsAt(3);
  ui->label_4->setPixmap(QPixmap::fromImage(cube.getSides().at(3).getImage()));
}

void importwindow::on_importimage5_clicked() {
  QString filename = QFileDialog::getOpenFileName(this,tr("Open File"), "C://", "JPG (*.jpg)");
  QImage newImage (filename);
  cube.setSide(4,ImportedImage(newImage));
  cube.setPixelsAt(4);
  ui->label_5->setPixmap(QPixmap::fromImage(cube.getSides().at(4).getImage()));
}

void importwindow::on_importimage6_clicked() {
  QString filename = QFileDialog::getOpenFileName(this,tr("Open File"), "C://", "JPG (*.jpg)");
  QImage newImage (filename);
  cube.setSide(5,ImportedImage(newImage));
  cube.setPixelsAt(5);
  ui->label_6->setPixmap(QPixmap::fromImage(cube.getSides().at(5).getImage()));
}

void importwindow::on_preview1_clicked() {
  ui->PreviewImage->setPixmap(QPixmap::fromImage(cube.getSides().at(0).getImage()));
}

void importwindow::on_preview2_clicked() {
  ui->PreviewImage->setPixmap(QPixmap::fromImage(cube.getSides().at(1).getImage()));
}

void importwindow::on_preview3_clicked() {
  ui->PreviewImage->setPixmap(QPixmap::fromImage(cube.getSides().at(2).getImage()));
}

void importwindow::on_preview4_clicked() {
  ui->PreviewImage->setPixmap(QPixmap::fromImage(cube.getSides().at(3).getImage()));
}

void importwindow::on_preview5_clicked() {
  ui->PreviewImage->setPixmap(QPixmap::fromImage(cube.getSides().at(4).getImage()));
}

void importwindow::on_pushButton_6_clicked() {
  ui->PreviewImage->setPixmap(QPixmap::fromImage(cube.getSides().at(5).getImage()));
}

void importwindow::on_exportfile_clicked() {
    QString fileName = QFileDialog::getSaveFileName(this,
            tr("Save Image"), "",
            tr("JPG (*.jpg)"));

}
