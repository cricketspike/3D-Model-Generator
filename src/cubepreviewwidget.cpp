#include <QVector3D>

#include "cubepreviewwidget.h"

#include <iostream>
using namespace std;

CubePreviewWidget::CubePreviewWidget(QWidget *parent) : QOpenGLWidget(parent),
                                                            m_vbo(QOpenGLBuffer::VertexBuffer),
                                                            m_program(0),
                                                            m_haveTextures(false),
                                                            m_useTextures(true),
                                                            zoom(0), tilt_x(0), tilt_y(0), tilt_z(0)
{
    // Allocate memory for the textures
    memset(textures, 0, sizeof(textures));
}

CubePreviewWidget::~CubePreviewWidget()
{
    makeCurrent();

    m_vbo.destroy();
    m_vao.destroy();
    delete m_program;
    if (m_haveTextures)
        for (int i = 0; i < 6; ++i)
            delete textures[i];

    doneCurrent();
}
void CubePreviewWidget::initializeGL()
{
    initializeOpenGLFunctions();
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_STENCIL_TEST);

    // Enable transparency
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Black background
    glClearColor(0,0,0,1);

    m_vao.create();
    m_vao.bind();

    GLfloat vertices[] = {
    /*
     *    X |  Y  |  Z  |       U | V
     * --------------------------------
     */
         0.5, -0.5,  0.5,       0,  0,      // Right
         0.5,  0.5,  0.5,       0,  1,
         0.5, -0.5, -0.5,       1,  0,
         0.5,  0.5, -0.5,       1,  1,

         0.5, -0.5, -0.5,       0,  0,      // Back
         0.5,  0.5, -0.5,       0,  1,
        -0.5, -0.5, -0.5,       1,  0,
        -0.5,  0.5, -0.5,       1,  1,

        -0.5, -0.5, -0.5,       0,  0,      // Left
        -0.5,  0.5, -0.5,       0,  1,
        -0.5, -0.5,  0.5,       1,  0,
        -0.5,  0.5,  0.5,       1,  1,


        -0.5, -0.5,  0.5,       0,  0,      // Front
        -0.5,  0.5,  0.5,       0,  1,
         0.5, -0.5,  0.5,       1,  0,
         0.5,  0.5,  0.5,       1,  1,


        -0.5, -0.5, -0.5,       0,  0,      // Bottom
        -0.5, -0.5,  0.5,       0,  1,
         0.5, -0.5, -0.5,       1,  0,
         0.5, -0.5,  0.5,       1,  1,


        -0.5,  0.5,  0.5,       0, 0,       // Top
        -0.5,  0.5, -0.5,       0, 1,
         0.5,  0.5,  0.5,       1, 0,
         0.5,  0.5, -0.5,       1, 1,
    };

    m_vbo.create();
    m_vbo.bind();
    m_vbo.setUsagePattern(QOpenGLBuffer::UsagePattern::StaticDraw);
    m_vbo.allocate(vertices, 6*4*5*sizeof(GLfloat));

    m_program = new QOpenGLShaderProgram(this);
    m_program->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/cubepreviewwidget.vert");
    m_program->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/cubepreviewwidget.frag");
    m_program->link();
    m_program->bind();

    m_uniform_model = m_program->uniformLocation("model");
    m_uniform_view = m_program->uniformLocation("view");
    m_uniform_projection = m_program->uniformLocation("projection");
    m_uniform_useTexture = m_program->uniformLocation("useTexture");

    m_program->setAttributeBuffer( "positionCoords", GL_FLOAT, 0, 3, sizeof(GLfloat)*5 );
    m_program->setAttributeBuffer( "textureCoords", GL_FLOAT, sizeof(GLfloat)*3, 2, sizeof(GLfloat)*5 );
    m_program->enableAttributeArray( "positionCoords" );
    m_program->enableAttributeArray( "textureCoords" );

    m_model.setToIdentity();
    m_view.setToIdentity();
    m_view.translate(QVector3D(0,0,-2));
    m_projection.setToIdentity();

    m_vao.release();

    m_program->release();
    m_vbo.release();

    connect(this, SIGNAL(frameSwapped()), this, SLOT(update()));
}

void CubePreviewWidget::resizeGL(int w, int h)
{
    m_projection.setToIdentity();
    m_projection.perspective(45.0, (float) w / (float) h, 0.1, 1000);
}

void CubePreviewWidget::paintGL()
{
    m_vao.bind();
    m_program->bind();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    m_model.setToIdentity();
    m_model.rotate(360*tilt_x, QVector3D(1, 0, 0));
    m_model.rotate(360*tilt_y, QVector3D(0, 1, 0));
    m_model.rotate(360*tilt_z, QVector3D(0, 0, 1));

    m_view.setToIdentity();
    m_view.translate(QVector3D(0,0,-3+(1.0*zoom)));

    m_program->setUniformValue(m_uniform_model, m_model);
    m_program->setUniformValue(m_uniform_view, m_view);
    m_program->setUniformValue(m_uniform_projection, m_projection);
    m_program->setUniformValue(m_uniform_useTexture, (m_useTextures && m_haveTextures ? 1 : 0));

    for (int i=0; i<6; i++) {
        if (m_useTextures && m_haveTextures)
            textures[i]->bind();
        glDrawArrays(GL_TRIANGLE_STRIP,  i*4, 4);
    }
    m_program->release();
    m_vao.release();
}

void CubePreviewWidget::setTilt_z(double value)
{
    tilt_z = value;
}

void CubePreviewWidget::setTilt_y(double value)
{
    tilt_y = value;
}

void CubePreviewWidget::setTilt_x(double value)
{
    tilt_x = value;
}

void CubePreviewWidget::setZoom(double value)
{
    zoom = value;
}

bool CubePreviewWidget::getUseTexture() const
{
    return m_useTextures;
}

void CubePreviewWidget::setUseTexture(bool value)
{
    m_useTextures = value;
}

void CubePreviewWidget::texturesFromBox(box b)
{
    makeCurrent();

    std::vector<ImportedImage> imgs = b.getSides();
    for (int i=0; i<imgs.size(); i++) {
        textures[i] = new QOpenGLTexture(imgs[i].getImage().mirrored());
        textures[i]->setMinificationFilter(QOpenGLTexture::Nearest);
        textures[i]->setMagnificationFilter(QOpenGLTexture::Linear);
    }

    m_haveTextures = true;

    doneCurrent();
}
