#ifndef CUBEMAPEDITORRASTERWIDGET_H
#define CUBEMAPEDITORRASTERWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QOpenGLFramebufferObject>
#include "cubemapeditorimage.h"

class CubeMapEditorRasterWidget : public QOpenGLWidget,
                                  protected QOpenGLFunctions
{
    Q_OBJECT

public:
    explicit CubeMapEditorRasterWidget(QWidget *parent = 0);


    ~CubeMapEditorRasterWidget();

    void setImage(CubeMapEditorImage* img);
    void raster(QString filename);

protected:
    void initializeGL();
    void paintGL();

private:

    QOpenGLVertexArrayObject vao;
    QOpenGLBuffer vbo;
    QOpenGLShaderProgram* program;

    // Cube map image
    CubeMapEditorImage* image;


    GLuint uniform_rotation;
    GLuint uniform_haveTexture;
    GLuint uniform_zoom;
    GLuint uniform_offset;
};

#endif // CUBEMAPEDITORRASTERWIDGET_H
