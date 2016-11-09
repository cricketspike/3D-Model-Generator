// Nir Jacobson
// njacobs1@ucsc.edu
// 2016-10-06
// Adapted from: http://doc.qt.io/qt-5/qtgui-openglwindow-example.html

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGlobal>
#include <QOpenGLShaderProgram>
#include <QScreen>


#include "openglwindow.h"

class MainWindow : public OpenGLWindow
{

public:
    float rot_z=0;
     MainWindow();
    MainWindow(GLfloat* verts,GLfloat*cols,GLuint num_verts);// (Pass in settings to affect the render)
    ~MainWindow();

    void initialize() Q_DECL_OVERRIDE;  // Create shader program, link, get attrs/uniforms, etc.
    void render() Q_DECL_OVERRIDE;      // 3D rendering

private:
    GLuint number_vertices;
    GLuint m_posAttr;                   // Address of shader attribute for vertex position
    GLuint m_colAttr;                   // Address of shader attribute for vertex color
    GLuint m_matrixUniform;             // Address of shader uniform for MVP matrix
GLfloat * vertices;
GLfloat * colors;
    QOpenGLShaderProgram* m_program;    // Shader program
};

#endif // MAINWINDOW_H
