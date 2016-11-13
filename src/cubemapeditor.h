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
    enum Face { Front, Right, Back, Left, Top, Bottom, NONE };

    explicit CubeMapEditor(QWidget *parent = 0);
    ~CubeMapEditor();

private slots:
    void selection(int);
    void on_pushButton_loadImage_clicked();

private:
    Ui::CubeMapEditor *ui;
};

#endif // CUBEMAPEDITOR_H
