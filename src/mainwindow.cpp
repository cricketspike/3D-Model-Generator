// Nir Jacobson
// njacobs1@ucsc.edu
// 2016-10-06
// Adapted from: http://doc.qt.io/qt-5/qtgui-openglwindow-example.html
#include <iostream>
#include <string>

#include "mainwaindow.h"

static const char* vertexShaderSource =
    "attribute highp vec4 posAttr;\n"
    "attribute lowp  vec4 colAttr;\n"
    "varying   lowp  vec4 col;\n"
    "uniform   highp mat4 matrix;\n"

    "void main() {\n"
    "   col = colAttr;\n"
    "   gl_Position = matrix * posAttr;\n"
    "}\n";

static const char* fragmentShaderSource =
    "varying lowp vec4 col;\n"

    "void main() {\n"
    "   gl_FragColor = col;\n"
    "}\n";
MainWindow::MainWindow()
    : m_program(0)
{}
MainWindow::MainWindow(GLfloat* verts,GLfloat*cols,GLuint num_verts)
    : m_program(0)
{
    number_vertices=num_verts;
    vertices=verts;
    colors=cols;
    // Pass in settings to affect the render
}

MainWindow::~MainWindow()
{
    delete m_program;
}

void MainWindow::initialize()
{
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);//This was working before :<


    // Create shader program
    m_program = new QOpenGLShaderProgram(this);
    m_program->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource);
    m_program->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSource);
    m_program->link();

    // Get attribute and uniform locations

    m_posAttr = m_program->attributeLocation("posAttr");
    m_colAttr = m_program->attributeLocation("colAttr");
    m_matrixUniform = m_program->uniformLocation("matrix");
}

void MainWindow::render()
{

glDepthFunc(GL_LEQUAL);
    rot_z++;
    const qreal retinaScale = devicePixelRatio();
    glViewport(0, 0, width() * retinaScale, height() * retinaScale);
    glClear(GL_DEPTH_BUFFER_BIT);
    glClear(GL_COLOR_BUFFER_BIT);
    m_program->bind();
    QMatrix4x4 matrix;
    matrix.perspective(60.0f, 4.0f/3.0f, 0.1f, 100.0f);
    matrix.translate(0, 0, -1);
    matrix.rotate(rot_z,rot_z/2,rot_z/2);
    m_program->setUniformValue(m_matrixUniform, matrix);



    std::cout<<sizeof(vertices);
    std::cout<<sizeof(colors);
    std::cout<<":" <<colors[44]<<endl;
    glVertexAttribPointer(m_posAttr, 3, GL_FLOAT, GL_FALSE, 0, vertices);
    glVertexAttribPointer(m_colAttr, 3, GL_FLOAT, GL_FALSE, 0, colors);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glDrawArrays(GL_TRIANGLES, 0, number_vertices);//last arg= how many vertices get shown

    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(0);

    m_program->release();
    renderLater();
}
