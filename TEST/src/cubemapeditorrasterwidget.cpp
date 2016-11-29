#include "cubemapeditorrasterwidget.h"

CubeMapEditorRasterWidget::CubeMapEditorRasterWidget(QWidget* parent) : QOpenGLWidget(parent),
                                                                        vbo(QOpenGLBuffer::VertexBuffer),
                                                                        program(0),
                                                                        image(0)
{

}


CubeMapEditorRasterWidget::~CubeMapEditorRasterWidget()
{
    makeCurrent();

    vbo.destroy();
    vao.destroy();
    delete program;

    doneCurrent();
}

void CubeMapEditorRasterWidget::setImage(CubeMapEditorImage* img)
{
    image = img;
    setMinimumSize(img->getImage().size());
    setMaximumSize(img->getImage().size());
}

void CubeMapEditorRasterWidget::raster(QString filename)
{

    setVisible(true);
    makeCurrent();

    QOpenGLFramebufferObject* fbo = new QOpenGLFramebufferObject(size());

    fbo->bind();
    paintGL();

    QImage img = fbo->toImage();
    img.save(filename);

    fbo->release();
    delete fbo;

    doneCurrent();
    setVisible(false);
}

void CubeMapEditorRasterWidget::initializeGL()
{
    initializeOpenGLFunctions();

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

    glClearColor(0,0,0,1);

    vao.create();
    vao.bind();

    GLfloat vertices[] = {
    /*
     *    X |  Y  |  Z  |       U | V
     * --------------------------------
     */
        -1.0, -1.0,  0.0,       0,  0,      // Left
        -1.0,  1.0,  0.0,       0,  1,
         1.0, -1.0,  0.0,       1,  0,
         1.0,  1.0,  0.0,       1,  1,

    };

    vbo.create();
    vbo.bind();
    vbo.setUsagePattern(QOpenGLBuffer::UsagePattern::StaticDraw);
    vbo.allocate(vertices, 4*5*sizeof(GLfloat));

    program = new QOpenGLShaderProgram(this);
    program->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/cubemapeditorrasterwidget.vert");
    program->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/cubemapeditorrasterwidget.frag");
    program->link();
    program->bind();

    uniform_rotation = program->uniformLocation("rotation");
    uniform_haveTexture = program->uniformLocation("haveTexture");
    uniform_zoom = program->uniformLocation("zoom");
    uniform_offset = program->uniformLocation("offset");

    program->setAttributeBuffer( "positionCoords", GL_FLOAT, 0, 3, sizeof(GLfloat)*5 );
    program->setAttributeBuffer( "textureCoords", GL_FLOAT, sizeof(GLfloat)*3, 2, sizeof(GLfloat)*5 );
    program->enableAttributeArray( "positionCoords" );
    program->enableAttributeArray( "textureCoords" );

    vao.release();

    program->release();
    vbo.release();
}

void CubeMapEditorRasterWidget::paintGL()
{
    vao.bind();
    program->bind();

    glClear(GL_COLOR_BUFFER_BIT);
    double zoom = 1.0;
    QPointF offset(0.0, 0.0);
    int rotation = 0;
    bool haveImage = false;

    if (image) {
        image->getFocus(zoom, offset);
        rotation = image->getRotation();
        haveImage = image->haveImage();
    }

    program->setUniformValue(uniform_rotation, rotation);
    program->setUniformValue(uniform_haveTexture, (haveImage ? 1 : 0));             // Whether image set for this face
    program->setUniformValue(uniform_zoom, (GLfloat)zoom);                          // Image zoom (scaling)
    program->setUniformValue(uniform_offset, offset);                               // Image offset (positioning)

    if (image)
        image->bindTexture();

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    program->release();
    vao.release();

}
