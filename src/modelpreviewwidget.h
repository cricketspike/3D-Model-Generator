#ifndef ModelPreviewWidget_H
#define ModelPreviewWidget_H

#include <QOpenGLWidget>
#include <QMatrix4x4>
#include <QOpenGLFunctions>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QOpenGLShader>
#include <QOpenGLTexture>
#include <algorithm>    // std::min

#include "ImportedImage.h"

class ModelPreviewWidget : public QOpenGLWidget,
                          protected QOpenGLFunctions
{
    Q_OBJECT


public slots:

    void renderModel(vector<GLfloat> faces,vector<GLfloat> colors);
public:
    explicit ModelPreviewWidget(QWidget *parent = 0);
    ~ModelPreviewWidget();

    void texturesFromBox(box& b);
    void setUseTexture(bool value);
    bool getUseTexture() const;

    void setZoom(double value);
    void setTilt_x(double value);
    void setTilt_y(double value);
    void setTilt_z(double value);
    void updateBuffers(float* coords);//have model edditor signal to this

protected:
    void initializeGL();
    void paintGL();

private:
    int spin=0;
    vector<GLfloat> m_faces;
    vector<GLfloat> m_colors_vec;
    GLuint m_number_vertices;
    GLuint m_posAttr;                   // Address of shader attribute for vertex position
    GLuint m_colAttr;                   // Address of shader attribute for vertex color
    GLuint m_matrixUniform;             // Address of shader uniform for MVP matrix
    GLfloat * m_vertices;
    GLfloat * m_colors;
    QOpenGLShaderProgram* m_program;    // Shader program

    QOpenGLTexture* textures[6];

    double zoom;
    double tilt_x;
    double tilt_y;
    double tilt_z;


};

#endif // ModelPreviewWidget_H
