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
    void resizeGL(int w, int h);
    void paintGL();

private:


    enum {
        POSITION_VB=0,//vertex buffer
        POSITION_IB=1,//index buffer
        NUM_BUFFERS=2, //number of buffers in enumeration
        TEXCOORD_VB=2,
        floats_per_vertex=3,
        verts_per_triangle=3
    };

    void initBuffers();

    GLuint m_vertexArrayObject;
    GLuint m_vertex_buffers[NUM_BUFFERS];
    unsigned int m_draw_count;

    QOpenGLVertexArrayObject m_vao;
    QOpenGLBuffer m_vbo;
    QOpenGLShaderProgram* m_program;

    QMatrix4x4 m_model;
    QMatrix4x4 m_view;
    QMatrix4x4 m_projection;
    bool m_haveTextures;
    bool m_useTextures;
    vector<GLfloat> m_faces;
    GLfloat *m_faces_by_vertices;
    GLfloat * m_faces_by_colors;
    size_t m_num_verts;
    unsigned int m_vertices_count;
    GLuint m_uniform_model;
    GLuint m_uniform_view;
    GLuint m_uniform_projection;
    GLuint m_uniform_useTexture;

    QOpenGLTexture* textures[6];

    double zoom;
    double spin;
    double tilt_x;
    double tilt_y;
    double tilt_z;


};

#endif // ModelPreviewWidget_H
