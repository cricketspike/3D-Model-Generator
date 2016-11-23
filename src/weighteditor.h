#ifndef WEIGHTEDITOR_H
#define WEIGHTEDITOR_H

#include <QDialog>
#include <vector>
#include "src/cubemapeditorimage.h"

namespace Ui {
class weighteditor;
}

class weighteditor : public QDialog
{
    Q_OBJECT

public:
    explicit weighteditor(QWidget *parent = 0);
    ~weighteditor();
    void loadImage (CubeMapEditorImage* newImage) {image = newImage;}
    //void getWeight (vector<vector<uint8_t*>> *newWeight){weight = newWeight;}

protected:
    void mousePressEvent(QMouseEvent* event);

private:
    Ui::weighteditor *ui;
    void closeEvent(QCloseEvent *event);
    CubeMapEditorImage* image;
    std::vector<std::vector<uint8_t>> weight;
};

#endif // WEIGHTEDITOR_H
