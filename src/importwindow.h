#ifndef IMPORTWINDOW_H
#define IMPORTWINDOW_H

#include <QMainWindow>
#include "src/ImportedImage.h"
namespace Ui {
class importwindow;
}

class importwindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit importwindow(QWidget *parent = 0);
    ~importwindow();


private slots:


    void on_importimage1_clicked();

    void on_importimage2_clicked();

    void on_importimage3_clicked();

    void on_importimage4_clicked();

    void on_importimage5_clicked();

    void on_importimage6_clicked();

    void on_preview1_clicked();

    void on_preview2_clicked();

    void on_preview3_clicked();

    void on_preview4_clicked();

    void on_preview5_clicked();

    void on_pushButton_6_clicked();

    void on_exportfile_clicked();

private:
    Ui::importwindow *ui;
    box cube;
    void setImage(int count);
};

#endif // IMPORTWINDOW_H
