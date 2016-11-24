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
                                                              selected_face(CubeMapEditor::Face::NONE),
                                                              projection_mode(ProjectionMode::None)
{
    images = new CubeMapEditorImage[6];
	grabKeyboard();
}

CubeMapEditorDisplay::~CubeMapEditorDisplay()
{
    releaseKeyboard();
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

bool CubeMapEditorDisplay::haveImage(CubeMapEditor::Face f)
{
    return images[f].haveImage();
}

void CubeMapEditorDisplay::loadImage(QImage image)
{
    images[selected_face].setImage(image);
    switch (selected_face) {
        case CubeMapEditor::Front:
            images[selected_face].setTmpPath("tmp/Front.jpg");
            break;
        case CubeMapEditor::Right:
            images[selected_face].setTmpPath("tmp/Right.jpg");
            break;
        case CubeMapEditor::Back:
            images[selected_face].setTmpPath("tmp/Back.jpg");
            break;
        case CubeMapEditor::Left:
            images[selected_face].setTmpPath("tmp/Left.jpg");
            break;
        case CubeMapEditor::Top:
            images[selected_face].setTmpPath("tmp/Top.jpg");
            break;
        case CubeMapEditor::Bottom:
            images[selected_face].setTmpPath("tmp/Bottom.jpg");
            break;
        case CubeMapEditor::NONE:
            break;
    }

}

CubeMapEditorImage* CubeMapEditorDisplay::getImage()
{
    if (selected_face == CubeMapEditor::NONE)
        return &images[0];

    return &images[selected_face];
}

CubeMapEditorImage* CubeMapEditorDisplay::getImage(CubeMapEditor::Face f)
{
    return &images[(int)f];
}

void CubeMapEditorDisplay::setProjectionMode(CubeMapEditorDisplay::ProjectionMode mode)
{
    projection_mode = mode;

    updateVertices();
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

void CubeMapEditorDisplay::updateVertices()
{
    GLfloat vertices[] = {
    /*
     *    X |  Y  |  Z  |       U | V
     * --------------------------------
     */
        -1.5, -0.5,  0.0,       0,  0,      // Left
        -1.5,  0.5,  0.0,       0,  1,
        -0.5, -0.5,  0.0,       1,  0,
        -0.5,  0.5,  0.0,       1,  1,

        -0.5,  0.5,  0.0,       0,  0,      // Top
        -0.5,  1.5,  0.0,       0,  1,
         0.5,  0.5,  0.0,       1,  0,
         0.5,  1.5,  0.0,       1,  1,

        -0.5, -0.5,  0.0,       0,  0,      // Front
        -0.5,  0.5,  0.0,       0,  1,
         0.5, -0.5,  0.0,       1,  0,
         0.5,  0.5,  0.0,       1,  1,

        -0.5, -1.5,  0.0,       0,  0,      // Bottom
        -0.5, -0.5,  0.0,       0,  1,
         0.5, -1.5,  0.0,       1,  0,
         0.5, -0.5,  0.0,       1,  1,

         0.5, -0.5,  0.0,       0,  0,      // Right
         0.5,  0.5,  0.0,       0,  1,
         1.5, -0.5,  0.0,       1,  0,
         1.5,  0.5,  0.0,       1,  1,

         1.5, -0.5,  0.0,       0,  0,      // Back
         1.5,  0.5,  0.0,       0,  1,
         2.5, -0.5,  0.0,       1,  0,
         2.5,  0.5,  0.0,       1,  1,

        -1.5,  0.5,  0.0,       0,  0,      // Projection Top Left
        -1.5,  1.5,  0.0,       0,  1,
        -0.5,  0.5,  0.0,       1,  0,
        -0.5,  1.5,  0.0,       1,  1,

        -1.5, -1.5,  0.0,       0,  0,      // Projection Bottom Left
        -1.5, -0.5,  0.0,       0,  1,
        -0.5, -1.5,  0.0,       1,  0,
        -0.5, -0.5,  0.0,       1,  1,

         0.5,  0.5,  0.0,       0,  0,      // Projection Top Right
         0.5,  1.5,  0.0,       0,  1,
         1.5,  0.5,  0.0,       1,  0,
         1.5,  1.5,  0.0,       1,  1,

         0.5, -1.5,  0.0,       0,  0,      // Projection Bottom Right
         0.5, -0.5,  0.0,       0,  1,
         1.5, -1.5,  0.0,       1,  0,
         1.5, -0.5,  0.0,       1,  1,

         1.5,  0.5,  0.0,       0,  0,      // Projection Top Far Right
         1.5,  1.5,  0.0,       0,  1,
         2.5,  0.5,  0.0,       1,  0,
         2.5,  1.5,  0.0,       1,  1,

         1.5, -1.5,  0.0,       0,  0,      // Projection Bottom Far Right
         1.5, -0.5,  0.0,       0,  1,
         2.5, -1.5,  0.0,       1,  0,
         2.5, -0.5,  0.0,       1,  1,


    };

    if (projection_mode == ProjectionMode::LeftAndRight) {
        vertices[120+3] = 1; vertices[120+4] = 0;
        vertices[125+3] = 0; vertices[125+4] = 0;
        vertices[130+3] = 1; vertices[130+4] = 1;
        vertices[135+3] = 0; vertices[135+4] = 1;

        vertices[140+3] = 0; vertices[140+4] = 1;
        vertices[145+3] = 1; vertices[145+4] = 1;
        vertices[150+3] = 0; vertices[150+4] = 0;
        vertices[155+3] = 1; vertices[155+4] = 0;

        vertices[160+3] = 0; vertices[160+4] = 1;
        vertices[165+3] = 1; vertices[165+4] = 1;
        vertices[170+3] = 0; vertices[170+4] = 0;
        vertices[175+3] = 1; vertices[175+4] = 0;

        vertices[180+3] = 1; vertices[180+4] = 0;
        vertices[185+3] = 0; vertices[185+4] = 0;
        vertices[190+3] = 1; vertices[190+4] = 1;
        vertices[195+3] = 0; vertices[195+4] = 1;
    } else if (projection_mode == ProjectionMode::TopAndBottom) {

        vertices[120+3] = 0; vertices[120+4] = 1;
        vertices[125+3] = 1; vertices[125+4] = 1;
        vertices[130+3] = 0; vertices[130+4] = 0;
        vertices[135+3] = 1; vertices[135+4] = 0;

        vertices[140+3] = 1; vertices[140+4] = 0;
        vertices[145+3] = 0; vertices[145+4] = 0;
        vertices[150+3] = 1; vertices[150+4] = 1;
        vertices[155+3] = 0; vertices[155+4] = 1;

        vertices[160+3] = 1; vertices[160+4] = 0;
        vertices[165+3] = 0; vertices[165+4] = 0;
        vertices[170+3] = 1; vertices[170+4] = 1;
        vertices[175+3] = 0; vertices[175+4] = 1;

        vertices[180+3] = 0; vertices[180+4] = 1;
        vertices[185+3] = 1; vertices[185+4] = 1;
        vertices[190+3] = 0; vertices[190+4] = 0;
        vertices[195+3] = 1; vertices[195+4] = 0;

        vertices[200+3] = 1; vertices[200+4] = 1;
        vertices[205+3] = 1; vertices[205+4] = 0;
        vertices[210+3] = 0; vertices[210+4] = 1;
        vertices[215+3] = 0; vertices[215+4] = 0;

        vertices[220+3] = 1; vertices[220+4] = 1;
        vertices[225+3] = 1; vertices[225+4] = 0;
        vertices[230+3] = 0; vertices[230+4] = 1;
        vertices[235+3] = 0; vertices[235+4] = 0;
    }

    vbo.bind();
    vbo.write(0, vertices, 12*4*5*sizeof(GLfloat));
    vbo.release();
}

void CubeMapEditorDisplay::initializeGL()
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
        -1.5, -0.5,  0.0,       0,  0,      // Left
        -1.5,  0.5,  0.0,       0,  1,
        -0.5, -0.5,  0.0,       1,  0,
        -0.5,  0.5,  0.0,       1,  1,

        -0.5,  0.5,  0.0,       0,  0,      // Top
        -0.5,  1.5,  0.0,       0,  1,
         0.5,  0.5,  0.0,       1,  0,
         0.5,  1.5,  0.0,       1,  1,

        -0.5, -0.5,  0.0,       0,  0,      // Front
        -0.5,  0.5,  0.0,       0,  1,
         0.5, -0.5,  0.0,       1,  0,
         0.5,  0.5,  0.0,       1,  1,

        -0.5, -1.5,  0.0,       0,  0,      // Bottom
        -0.5, -0.5,  0.0,       0,  1,
         0.5, -1.5,  0.0,       1,  0,
         0.5, -0.5,  0.0,       1,  1,

         0.5, -0.5,  0.0,       0,  0,      // Right
         0.5,  0.5,  0.0,       0,  1,
         1.5, -0.5,  0.0,       1,  0,
         1.5,  0.5,  0.0,       1,  1,

         1.5, -0.5,  0.0,       0,  0,      // Back
         1.5,  0.5,  0.0,       0,  1,
         2.5, -0.5,  0.0,       1,  0,
         2.5,  0.5,  0.0,       1,  1,

        -1.5,  0.5,  0.0,       0,  0,      // Projection Top Left
        -1.5,  1.5,  0.0,       0,  1,
        -0.5,  0.5,  0.0,       1,  0,
        -0.5,  1.5,  0.0,       1,  1,

        -1.5, -1.5,  0.0,       0,  0,      // Projection Bottom Left
        -1.5, -0.5,  0.0,       0,  1,
        -0.5, -1.5,  0.0,       1,  0,
        -0.5, -0.5,  0.0,       1,  1,

         0.5,  0.5,  0.0,       0,  0,      // Projection Top Right
         0.5,  1.5,  0.0,       0,  1,
         1.5,  0.5,  0.0,       1,  0,
         1.5,  1.5,  0.0,       1,  1,

         0.5, -1.5,  0.0,       0,  0,      // Projection Bottom Right
         0.5, -0.5,  0.0,       0,  1,
         1.5, -1.5,  0.0,       1,  0,
         1.5, -0.5,  0.0,       1,  1,

         1.5,  0.5,  0.0,       0,  0,      // Projection Top Far Right
         1.5,  1.5,  0.0,       0,  1,
         2.5,  0.5,  0.0,       1,  0,
         2.5,  1.5,  0.0,       1,  1,

         1.5, -1.5,  0.0,       0,  0,      // Projection Bottom Far Right
         1.5, -0.5,  0.0,       0,  1,
         2.5, -1.5,  0.0,       1,  0,
         2.5, -0.5,  0.0,       1,  1,


    };

    vbo.create();
    vbo.bind();
    vbo.setUsagePattern(QOpenGLBuffer::UsagePattern::StaticDraw);
    vbo.allocate(vertices, 12*4*5*sizeof(GLfloat));

    program = new QOpenGLShaderProgram(this);
    program->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/cubemapeditordisplay.vert");
    program->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/cubemapeditordisplay.frag");
    program->link();
    program->bind();

    uniform_model = program->uniformLocation("model");
    uniform_view = program->uniformLocation("view");
    uniform_projection = program->uniformLocation("projection");
    uniform_haveTexture = program->uniformLocation("haveTexture");
    uniform_isProjection = program->uniformLocation("isProjection");
    uniform_rotation = program->uniformLocation("rotation");
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

    // Starting with the faces, not their projections
    program->setUniformValue(uniform_isProjection, 0);

    // Draw each face
    for (int i=0; i<6; i++) {
        double zoom;
        QPointF offset;
        images[i].getFocus(zoom, offset);

        program->setUniformValue(uniform_rotation, images[i].getRotation());
        program->setUniformValue(uniform_haveTexture, (images[i].haveImage() ? 1 : 0)); // Whether image set for this face
        program->setUniformValue(uniform_zoom, (GLfloat)zoom);                          // Image zoom (scaling)
        program->setUniformValue(uniform_offset, offset);                               // Image offset (positioning)
        images[i].bindTexture();

        glDrawArrays(GL_TRIANGLE_STRIP, i*4, 4);
    }

    if (projection_mode != ProjectionMode::None) {
        program->setUniformValue(uniform_isProjection, 1);

        if (projection_mode == ProjectionMode::LeftAndRight) {

            double zoom;
            QPointF offset;

            CubeMapEditorImage* image = &images[CubeMapEditor::Left];
            image->getFocus(zoom, offset);

            program->setUniformValue(uniform_rotation, image->getRotation());
            program->setUniformValue(uniform_haveTexture, (image->haveImage() ? 1 : 0));
            program->setUniformValue(uniform_zoom, (GLfloat)zoom);
            program->setUniformValue(uniform_offset, offset);
            image->bindTexture();

            glDrawArrays(GL_TRIANGLE_STRIP, (6+0)*4, 4);
            glDrawArrays(GL_TRIANGLE_STRIP, (6+1)*4, 4);



            image = &images[CubeMapEditor::Right];
            image->getFocus(zoom, offset);

            program->setUniformValue(uniform_rotation, image->getRotation());
            program->setUniformValue(uniform_haveTexture, (image->haveImage() ? 1 : 0));
            program->setUniformValue(uniform_zoom, (GLfloat)zoom);
            program->setUniformValue(uniform_offset, offset);
            image->bindTexture();

            glDrawArrays(GL_TRIANGLE_STRIP, (6+2)*4, 4);
            glDrawArrays(GL_TRIANGLE_STRIP, (6+3)*4, 4);



//            image = &images[CubeMapEditor::Back];
//            image->getFocus(zoom, offset);

//            program->setUniformValue(uniform_rotation, image->getRotation());
//            program->setUniformValue(uniform_haveTexture, (image->haveImage() ? 1 : 0));
//            program->setUniformValue(uniform_zoom, (GLfloat)zoom);
//            program->setUniformValue(uniform_offset, offset);
//            image->bindTexture();

//            glDrawArrays(GL_TRIANGLE_STRIP, (6+4)*4, 4);
//            glDrawArrays(GL_TRIANGLE_STRIP, (6+5)*4, 4);

        } else if (projection_mode == ProjectionMode::TopAndBottom) {

            double zoom;
            QPointF offset;

            CubeMapEditorImage* image = &images[CubeMapEditor::Top];
            image->getFocus(zoom, offset);

            program->setUniformValue(uniform_rotation, image->getRotation());
            program->setUniformValue(uniform_haveTexture, (image->haveImage() ? 1 : 0));
            program->setUniformValue(uniform_zoom, (GLfloat)zoom);
            program->setUniformValue(uniform_offset, offset);
            image->bindTexture();

            glDrawArrays(GL_TRIANGLE_STRIP, (6+0)*4, 4);
            glDrawArrays(GL_TRIANGLE_STRIP, (6+2)*4, 4);
            glDrawArrays(GL_TRIANGLE_STRIP, (6+4)*4, 4);



            image = &images[CubeMapEditor::Bottom];
            image->getFocus(zoom, offset);

            program->setUniformValue(uniform_rotation, image->getRotation());
            program->setUniformValue(uniform_haveTexture, (image->haveImage() ? 1 : 0));
            program->setUniformValue(uniform_zoom, (GLfloat)zoom);
            program->setUniformValue(uniform_offset, offset);
            image->bindTexture();

            glDrawArrays(GL_TRIANGLE_STRIP, (6+1)*4, 4);
            glDrawArrays(GL_TRIANGLE_STRIP, (6+3)*4, 4);
            glDrawArrays(GL_TRIANGLE_STRIP, (6+5)*4, 4);
        }
    }

    program->release();
    vao.release();

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
	Scene::draw(painter);
    Tool::draw(painter);
    //drawRulers(painter);  - Functionality removed
}

void CubeMapEditorDisplay::mouseMoveEvent(QMouseEvent* event)
{
    Tool::updateMouse((double)event->pos().x(), (double)event->pos().y());
    if(event->buttons() == Qt::LeftButton) {
        Tool::onMouseDrag();
    }
	
    if(Tool::selected == Tool::T_MOVER) {
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
}

void CubeMapEditorDisplay::mousePressEvent(QMouseEvent* event)
{
    Tool::updateMouse((double)event->pos().x(), (double)event->pos().y());
    if(event->button() == Qt::LeftButton)
        Tool::onMouseLeftPress();
    else if(event->button() == Qt::RightButton)
        Tool::onMouseRightPress();
	
    if(Tool::selected == Tool::T_MOVER) {
        if (event->buttons() == Qt::LeftButton) {                               //    Left-click
            last_mouse_pos = event->pos();
        } else if (selected_face != CubeMapEditor::Face::NONE) {                //    Right-click
            images[selected_face].rotate();
        }
    }
}

void CubeMapEditorDisplay::mouseReleaseEvent(QMouseEvent* event)
{
    Tool::updateMouse((double)event->pos().x(), (double)event->pos().y());
    if(event->button() == Qt::LeftButton)
        Tool::onMouseLeftRelease();
    else if(event->button() == Qt::RightButton)
        Tool::onMouseRightRelease();
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

void CubeMapEditorDisplay::keyPressEvent(QKeyEvent* event) {
    switch(event->key()) {
    case Qt::Key_1:
        Tool::set(Tool::T_POINTER);
        break;
    case Qt::Key_2:
        Tool::set(Tool::T_RULER);
        break;
    case Qt::Key_3:
        Tool::set(Tool::T_PICKER);
        break;
    case Qt::Key_4:
        Tool::set(Tool::T_MOVER);
        break;
    case Qt::Key_0: {
        QColorDialog picker;
        picker.setCurrentColor(QColor(Tool::color.r*255,Tool::color.g*255,Tool::color.b*255));
        picker.exec();
        int red, green, blue;
        picker.selectedColor().getRgb(&red, &green, &blue);
        Tool::color.r = red/255.0;
        Tool::color.g = green/255.0;
        Tool::color.b = blue/255.0;
    } break;
    case Qt::Key_Minus:
        Tool::Model::color = Tool::color;
        break;
    case Qt::Key_Equal:
        Tool::Null::color = Tool::color;
        break;
    case Qt::Key_Control:
        Tool::MODIFIER |= Tool::M_CTRL;
        break;
    }
}

void CubeMapEditorDisplay::keyReleaseEvent(QKeyEvent* event) {
    switch(event->key()) {
        case Qt::Key_Control:
        Tool::MODIFIER &= ~Tool::M_CTRL;
        break;
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
