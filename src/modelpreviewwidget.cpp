#include <QVector3D>

#include "modelpreviewwidget.h"

#include <iostream>
using namespace std;


void ModelPreviewWidget::renderModel(vector<GLfloat> faces,vector<GLfloat> colors){
    m_faces=faces;//need this to keep array in scope
    m_faces_by_vertices= &m_faces[0];
    m_faces_by_colors= &colors[0];
    m_num_verts=faces.size();
    cout<<"TEST SLOT "<< faces.size() <<endl;
}

ModelPreviewWidget::ModelPreviewWidget(QWidget *parent) : QOpenGLWidget(parent),
                                                            m_vbo(QOpenGLBuffer::VertexBuffer),
                                                            m_program(0),
                                                            m_haveTextures(false),
                                                            m_useTextures(true),
                                                            zoom(0), tilt_x(0), tilt_y(0), tilt_z(0)
{
    // Allocate memory for the textures
    memset(textures, 0, sizeof(textures));
}

ModelPreviewWidget::~ModelPreviewWidget()
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
void ModelPreviewWidget::initializeGL()
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

    m_vbo.create();
    m_vbo.bind();
    m_vbo.setUsagePattern(QOpenGLBuffer::UsagePattern::DynamicDraw);
    m_vbo.allocate(m_faces_by_vertices,m_num_verts*3);

    m_program = new QOpenGLShaderProgram(this);
    m_program->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/ModelPreviewWidget.vert");
    m_program->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/ModelPreviewWidget.frag");
    m_program->link();
    m_program->bind();

    m_uniform_model = m_program->uniformLocation("model");
    m_uniform_view = m_program->uniformLocation("view");
    m_uniform_projection = m_program->uniformLocation("projection");
    m_uniform_useTexture = m_program->uniformLocation("useTexture");

    m_program->setAttributeBuffer( "positionCoords", GL_FLOAT, 0, 3, sizeof(GLfloat)*3 );
    m_program->setAttributeBuffer( "textureCoords", GL_FLOAT, sizeof(GLfloat)*3, 3, sizeof(GLfloat)*3 );
    m_program->enableAttributeArray( "positionCoords" );
    m_program->enableAttributeArray( "textureCoords" );

    m_model.setToIdentity();
    m_view.setToIdentity();
    m_view.translate(QVector3D(0,0,-2));
    m_projection.setToIdentity();

    m_vao.release();

    m_program->release();
    m_vbo.release();

    QImage img0( ":/images/image0.jpg" );
    QImage img1( ":/images/image1.jpg" );
    QImage img2( ":/images/image2.jpg" );
    QImage img3( ":/images/image3.jpg" );
    QImage img4( ":/images/image4.jpg" );
    QImage img5( ":/images/image5.jpg" );

    vector<QImage> images;
    images.push_back(img0);
    images.push_back(img1);
    images.push_back(img2);
    images.push_back(img3);
    images.push_back(img4);
    images.push_back(img5);

    box b = box(images);
    //texturesFromBox(b);

    connect(this, SIGNAL(frameSwapped()), this, SLOT(update()));
    spin=0;
}

void ModelPreviewWidget::resizeGL(int w, int h)
{
    m_projection.setToIdentity();
    m_projection.perspective(40.0f, (float) w / (float) h, 0.1f, 1000);
}

void ModelPreviewWidget::paintGL()
{
tilt_y+=.01;
spin+=9;
string x;
//cin>>x;
    m_program->setAttributeBuffer( "positionCoords", GL_FLOAT, 0, 3, sizeof(GLfloat)*3 );
    m_program->setAttributeBuffer( "textureCoords", GL_FLOAT, sizeof(GLfloat)*3, 3, sizeof(GLfloat)*3 );
    m_program->enableAttributeArray( "positionCoords" );
    m_program->enableAttributeArray( "textureCoords" );
    m_vao.bind();
    m_vbo.bind();

    m_vbo.allocate(m_faces_by_vertices,m_num_verts*verts_per_triangle);

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

    cout<<"TEST10 "<<m_num_verts<<endl;

    for (int i=0;(i< m_num_verts); i++) {
       //cout <<"vert"<<i<<": "<<m_faces[i]<<", "<<m_faces[i+1]<<", "<<m_faces[i+2]<<endl;

        if (m_useTextures && m_haveTextures)
        {
            textures[i]->bind();
        }

        glDrawArrays(GL_TRIANGLES,  i * verts_per_triangle, verts_per_triangle);
    }cout<<endl;
    m_program->release();
    m_vao.release();
    m_vbo.release();
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

bool ModelPreviewWidget::getUseTexture() const
{
    return m_useTextures;
}

void ModelPreviewWidget::setUseTexture(bool value)
{
    m_useTextures = value;
}

void ModelPreviewWidget::texturesFromBox(box& b)
{
    std::vector<ImportedImage> imgs = b.getSides();
    for (int i=0; i<imgs.size(); i++) {
        textures[i] = new QOpenGLTexture(imgs[i].getImage().mirrored());
        textures[i]->setMinificationFilter(QOpenGLTexture::Nearest);
        textures[i]->setMagnificationFilter(QOpenGLTexture::Linear);
    }

    m_haveTextures = true;
}
