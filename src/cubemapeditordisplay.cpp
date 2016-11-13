#include <iostream>
#include <string>
#include <QPainter>
#include <QGuiApplication>
#include "cubemapeditor.h"
#include "cubemapeditordisplay.h"

CubeMapEditorDisplay::CubeMapEditorDisplay(QWidget* parent) : QOpenGLWidget(parent),
                                                              vbo(QOpenGLBuffer::VertexBuffer),
                                                              program(0),
                                                              zoom(1.0),
                                                              offset(0.0, 0.0),
                                                              selected_face(CubeMapEditor::Face::NONE)
{
    images = new CubeMapEditorImage[6];
}

CubeMapEditorDisplay::~CubeMapEditorDisplay()
{
    makeCurrent();

    vbo.destroy();
    vao.destroy();
    delete program;
    delete [] images;

    doneCurrent();
}

void CubeMapEditorDisplay::selectFace(CubeMapEditor::Face face)
{
    selected_face = face;
}

void CubeMapEditorDisplay::loadImage(QImage image)
{
    images[selected_face].setImage(image);
}

void CubeMapEditorDisplay::getFocus(double& zoom, QPointF& offset)
{
    switch (selected_face) {
    case CubeMapEditor::Front:
    case CubeMapEditor::Right:
    case CubeMapEditor::Back:
    case CubeMapEditor::Left:
    case CubeMapEditor::Top:
    case CubeMapEditor::Bottom:
        images[selected_face].getFocus(zoom, offset);
        break;
    case CubeMapEditor::NONE:
        zoom = this->zoom;
        offset = this->offset;
        break;

    }
}

void CubeMapEditorDisplay::setFocus(double zoom, QPointF offset)
{
    switch (selected_face) {
    case CubeMapEditor::Front:
    case CubeMapEditor::Right:
    case CubeMapEditor::Back:
    case CubeMapEditor::Left:
    case CubeMapEditor::Top:
    case CubeMapEditor::Bottom:
        images[selected_face].setFocus(zoom, offset);
        break;
    case CubeMapEditor::NONE:
        this->zoom = zoom;
        this->offset = offset;

        /* To apply the new focus:
         *   - Scale the original 5x4 viewport based on zoom
         *   - Translate the viewport based on offset
         */
        matrix_projection.setToIdentity();
        matrix_projection.ortho(-2.0/zoom-offset.x(), 3.0/zoom-offset.x(), -2.0/zoom-offset.y(), 2.0/zoom-offset.y(), -1, 1);

        break;

    }
}

void CubeMapEditorDisplay::initializeGL()
{
    initializeOpenGLFunctions();

    glClearColor(0,0,0,1);

    vao.create();
    vao.bind();

    GLfloat vertices[] = {
    /*
     *    X |  Y  |  Z  |       U | V
     * --------------------------------
     */
        -0.5, -0.5,  0.0,       0,  0,      // Front
        -0.5,  0.5,  0.0,       0,  1,
         0.5, -0.5,  0.0,       1,  0,
         0.5,  0.5,  0.0,       1,  1,

         0.5, -0.5,  0.0,       0,  0,      // Right
         0.5,  0.5,  0.0,       0,  1,
         1.5, -0.5,  0.0,       1,  0,
         1.5,  0.5,  0.0,       1,  1,

         1.5, -0.5,  0.0,       0,  0,      // Back
         1.5,  0.5,  0.0,       0,  1,
         2.5, -0.5,  0.0,       1,  0,
         2.5,  0.5,  0.0,       1,  1,

        -1.5, -0.5,  0.0,       0,  0,      // Left
        -1.5,  0.5,  0.0,       0,  1,
        -0.5, -0.5,  0.0,       1,  0,
        -0.5,  0.5,  0.0,       1,  1,

        -0.5,  0.5,  0.0,       0,  0,      // Top
        -0.5,  1.5,  0.0,       0,  1,
         0.5,  0.5,  0.0,       1,  0,
         0.5,  1.5,  0.0,       1,  1,

        -0.5, -1.5,  0.0,       0,  0,      // Bottom
        -0.5, -0.5,  0.0,       0,  1,
         0.5, -1.5,  0.0,       1,  0,
         0.5, -0.5,  0.0,       1,  1,
    };

    vbo.create();
    vbo.bind();
    vbo.setUsagePattern(QOpenGLBuffer::UsagePattern::StaticDraw);
    vbo.allocate(vertices, 6*4*5*sizeof(GLfloat));

    program = new QOpenGLShaderProgram(this);
    program->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/cubemapeditordisplay.vert");
    program->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/cubemapeditordisplay.frag");
    program->link();
    program->bind();

    uniform_model = program->uniformLocation("model");
    uniform_view = program->uniformLocation("view");
    uniform_projection = program->uniformLocation("projection");
    uniform_haveTexture = program->uniformLocation("haveTexture");
    uniform_zoom = program->uniformLocation("zoom");
    uniform_offset = program->uniformLocation("offset");

    program->setAttributeBuffer( "positionCoords", GL_FLOAT, 0, 3, sizeof(GLfloat)*5 );
    program->setAttributeBuffer( "textureCoords", GL_FLOAT, sizeof(GLfloat)*3, 2, sizeof(GLfloat)*5 );
    program->enableAttributeArray( "positionCoords" );
    program->enableAttributeArray( "textureCoords" );

    matrix_model.setToIdentity();
    matrix_view.setToIdentity();
    matrix_projection.setToIdentity();

    /* Cube map has:
     *   - Front face centered at origin
     *   - Face side length of 1.0
     *   - 0.5 border in the viewport
     *
     * So:
     *   - Viewport X range: [-2,+3]
     *   - Viewport Y range: [-2,+2]
     *
     */
    matrix_projection.ortho(-2, 3, -2, 2, -1, 1);

    program->setUniformValue(uniform_model, matrix_model);
    program->setUniformValue(uniform_view, matrix_view);
    program->setUniformValue(uniform_projection, matrix_projection);

    vao.release();

    program->release();
    vbo.release();

    connect(this, SIGNAL(frameSwapped()), this, SLOT(update()));
}

void CubeMapEditorDisplay::paintGL()
{
    vao.bind();
    program->bind();

    glClear(GL_COLOR_BUFFER_BIT);

    // Projection matrix (viewport scaling & positioning)
    program->setUniformValue(uniform_projection, matrix_projection);

    // Draw each face
    for (int i=0; i<6; i++) {
        double zoom;
        QPointF offset;
        images[i].getFocus(zoom, offset);

        program->setUniformValue(uniform_haveTexture, (images[i].haveImage() ? 1 : 0)); // Whether image set for this face
        program->setUniformValue(uniform_zoom, (GLfloat)zoom);                          // Image zoom (scaling)
        program->setUniformValue(uniform_offset, offset);                               // Image offset (positioning)
        images[i].bindTexture();

        glDrawArrays(GL_TRIANGLE_STRIP,  i*4, 4);
    }

    program->release();
    vao.release();

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    drawRulers(painter);
}

void CubeMapEditorDisplay::mouseMoveEvent(QMouseEvent* event)
{
    if (event->buttons() == Qt::LeftButton) {
        // Generate a vector (QPointF) describing the mouse motion

        QPoint mouse_pos = event->pos();
        QPoint v = (mouse_pos - last_mouse_pos);
        QPointF fv(v.x(), -v.y());
        fv /= 1000;

        if (selected_face != CubeMapEditor::Face::NONE) {
            // Alter the positioning of the selected face using mouse motion vector

            double zoom;
            QPointF offset;
            images[selected_face].getFocus(zoom, offset);
            images[selected_face].setFocus(zoom, offset+fv);
        } else {
            // Alter the positioning of the display using mouse motion vector

            offset += fv;
            setFocus(zoom, offset);
        }

        last_mouse_pos = mouse_pos;
    }

}

void CubeMapEditorDisplay::mousePressEvent(QMouseEvent* event)
{

    if (event->modifiers().testFlag(Qt::ShiftModifier)) {                       // Shift pressed

        double nx = ((double)event->pos().x())/width();
        double ny = ((double)event->pos().y())/height();

        DisplayRuler match_ruler;
        if (event->modifiers().testFlag(Qt::ControlModifier)) {                 //    Control pressed
           match_ruler.orientation = DisplayRuler::Orientation::Vertical;
           match_ruler.normalized_offset = nx;
        } else {                                                                //    Control not pressed
            match_ruler.orientation = DisplayRuler::Orientation::Horizontal;
            match_ruler.normalized_offset = ny;
        }

        if (event->buttons() == Qt::LeftButton) {                               //    Left-click
            addRuler(match_ruler);
        } else {                                                                //    Right-click
            removeRuler(match_ruler);
        }

    } else {                                                                    // Shift not pressed

        if (event->buttons() == Qt::LeftButton) {                               //    Left-click
            last_mouse_pos = event->pos();
        } else if (selected_face != CubeMapEditor::Face::NONE) {                //    Right-click
            images[selected_face].rotate();
        }

    }
}

void CubeMapEditorDisplay::wheelEvent(QWheelEvent* event)
{
    if (selected_face != CubeMapEditor::Face::NONE) {
        // Alter the zoom of the selected face using mouse wheel movement

        double zoom;
        QPointF offset;
        images[selected_face].getFocus(zoom, offset);
        zoom += (double)(event->angleDelta().y())/1200.0;
        images[selected_face].setFocus(zoom, offset);
    } else {
        // Alter the zoom of the display using mouse wheel movement

        zoom += (double)(event->angleDelta().y())/1200.0;
        setFocus(zoom, offset);
    }
}
void CubeMapEditorDisplay::addRuler(DisplayRuler r) {
    rulers.append(r);
}

void CubeMapEditorDisplay::removeRuler(DisplayRuler r)
{
    QMutableListIterator<DisplayRuler> i(rulers);
    while (i.hasNext()) {
        DisplayRuler ri = i.next();

        if (ri.orientation == r.orientation)
            if (abs(ri.normalized_offset - r.normalized_offset) <= 0.05)
                i.remove();
    }
}

void CubeMapEditorDisplay::drawRulers(QPainter& p)
{
    p.setPen(QPen(QColor(0,255,255)));

    QListIterator<DisplayRuler> i(rulers);
    while (i.hasNext()) {
        DisplayRuler ri = i.next();

        if (ri.orientation == DisplayRuler::Orientation::Horizontal) {
            p.drawLine(0, ri.normalized_offset*height(), width(), ri.normalized_offset*height());
        } else {
            p.drawLine(ri.normalized_offset*width(), 0, ri.normalized_offset*width(), height());
        }
    }
}
