#ifndef CUBEPREVIEWWIDGET_H
#define CUBEPREVIEWWIDGET_H

#include <QOpenGLWidget>
#include <QMatrix4x4>
#include <QOpenGLFunctions>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QOpenGLShader>
#include <QOpenGLTexture>

#include "ImportedImage.h"

class CubePreviewWidget : public QOpenGLWidget,
                          protected QOpenGLFunctions
{
    Q_OBJECT
public:
    explicit CubePreviewWidget(QWidget *parent = 0);
    ~CubePreviewWidget();

    void texturesFromBox(box& b);
    void setUseTexture(bool value);
    bool getUseTexture() const;

    void setZoom(double value);
    void setTilt_x(double value);
    void setTilt_y(double value);
    void setTilt_z(double value);

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

private:
    QOpenGLVertexArrayObject m_vao;
    QOpenGLBuffer m_vbo;
    QOpenGLShaderProgram* m_program;

    QMatrix4x4 m_model;
    QMatrix4x4 m_view;
    QMatrix4x4 m_projection;

    bool m_haveTextures;
    bool m_useTextures;

    GLuint m_uniform_model;
    GLuint m_uniform_view;
    GLuint m_uniform_projection;
    GLuint m_uniform_useTexture;

    QOpenGLTexture* textures[6];

    double zoom;
    double tilt_x;
    double tilt_y;
    double tilt_z;

signals:

public slots:
};

#endif // CUBEPREVIEWWIDGET_H
