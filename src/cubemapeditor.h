#ifndef CUBEMAPEDITOR_H
#define CUBEMAPEDITOR_H

#include <QMainWindow>

/*
 * This class provides a UI for editing/arranging six images
 * into a cube map, for ColoredVertexMatrix generation.
 *
 */

namespace Ui {
class CubeMapEditor;
}

class CubeMapEditor : public QMainWindow
{
    Q_OBJECT

public:
    int c;
    char **v={};
    void setC(int cin){c=cin;}
    enum Face { Left, Top, Front, Bottom, Right, Back, NONE };

    explicit CubeMapEditor(QWidget *parent = 0);
    ~CubeMapEditor();
    bool allHaveImage();

private slots:
    void selection(int);
    void on_pushButton_loadImage_clicked();
    void on_pushButton_clicked();
    void on_comboBox_projection_currentIndexChanged(int index);
    void on_pushButton_weight_clicked();

    void on_pushButton_saveCube_clicked();

private:
    Ui::CubeMapEditor *ui;
    std::vector<std::vector<uint8_t>> weight;
};

#endif // CUBEMAPEDITOR_H
