#include <QVector3D>

#include "modelpreviewwidget.h"

#include <iostream>
using namespace std;


ModelPreviewWidget::ModelPreviewWidget(QWidget *parent):QOpenGLWidget(parent),
    zoom(0), tilt_x(0), tilt_y(0), tilt_z(0), m_program(0)

{}

void ModelPreviewWidget::renderModel(vector<GLfloat> faces,vector<GLfloat> colors){
    m_faces=faces;//need this to keep array in scope
    m_vertices= &m_faces[0];
    m_colors_vec=colors;//need this so array works
    m_colors= &m_colors_vec[0];
    m_number_vertices=faces.size()/3;
    cout<<m_number_vertices;
    cout<<"TEST SLOT "<< faces.size() <<endl;
}



ModelPreviewWidget::~ModelPreviewWidget()
{
    makeCurrent();
     delete m_program;
    doneCurrent();
}

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
void ModelPreviewWidget::initializeGL()
{    initializeOpenGLFunctions();
     glEnable(GL_DEPTH_TEST);
     glEnable(GL_STENCIL_TEST);


     // Black background
     glClearColor(0,0,0,1);

   // glShadeModel(GL_SMOOTH);//This was working before :<


    // Create shader program
    m_program = new QOpenGLShaderProgram(this);
    m_program->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource);
    m_program->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSource);
    m_program->link();

    // Get attribute and uniform locations

    m_posAttr = m_program->attributeLocation("posAttr");
    m_colAttr = m_program->attributeLocation("colAttr");
    m_matrixUniform = m_program->uniformLocation("matrix");
     connect(this, SIGNAL(frameSwapped()), this, SLOT(update()));

}


void ModelPreviewWidget::paintGL()
{
    cout<<"TESTY";
    glDepthFunc(GL_LEQUAL);
        spin++;
        const qreal retinaScale = devicePixelRatio();
        glViewport(0, 0, width() * retinaScale, height() * retinaScale);
        glClear(GL_DEPTH_BUFFER_BIT);
        glClear(GL_COLOR_BUFFER_BIT);

        m_program->bind();

        QMatrix4x4 matrix;
        matrix.perspective(60.0f, 4.0f/3.0f, 0.1f, 100.0f);
        matrix.translate(0, 0, -1);
        matrix.rotate(spin,spin/2,spin/2);
        m_program->setUniformValue(m_matrixUniform, matrix);




        cout<<sizeof(m_vertices);
        cout<<sizeof(m_colors);
        std::cout<<":" <<m_colors[44]<<endl;
        glVertexAttribPointer(m_posAttr, 3, GL_FLOAT, GL_FALSE, 0, m_vertices);
        glVertexAttribPointer(m_colAttr, 3, GL_FLOAT, GL_FALSE, 0, m_colors);

        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glDrawArrays(GL_TRIANGLES, 0, m_number_vertices);//last arg= how many vertices get shown

        glDisableVertexAttribArray(1);
        glDisableVertexAttribArray(0);

        m_program->release();
}

void ModelPreviewWidget::setTilt_z(double value)
{
    tilt_z = value;
}

void ModelPreviewWidget::setTilt_y(double value)
{
    tilt_y = value;
}

void ModelPreviewWidget::setTilt_x(double value)
{
    tilt_x = value;
}

void ModelPreviewWidget::setZoom(double value)
{
    zoom = value;
}
