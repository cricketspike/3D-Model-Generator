#include "cubemapeditorimage.h"

CubeMapEditorImage::CubeMapEditorImage(QObject *parent) : QObject(parent),
                                                          have_image(false),
                                                          texture(0),
                                                          zoom(1.0),
                                                          offset(0.0, 0.0),
                                                          rotation(0)
{

}

CubeMapEditorImage::~CubeMapEditorImage()
{
    if (have_image)
        delete texture;
}

void CubeMapEditorImage::setPath(QString path)
{
    this->path = path;
}

void CubeMapEditorImage::setImage(QImage image)
{
    if (have_image)
        delete texture;

    this->image = image;

    // Image --> Texture
    this->texture = new QOpenGLTexture(image.mirrored());
    this->texture->setWrapMode(QOpenGLTexture::WrapMode::ClampToEdge);
    this->texture->setMinificationFilter(QOpenGLTexture::Nearest);
    this->texture->setMagnificationFilter(QOpenGLTexture::Linear);

    // Default focus
    this->offset = QPointF(0, 0);
    this->zoom = 1.0;

    this->have_image = true;
}

bool CubeMapEditorImage::haveImage() const
{
    return have_image;
}

QImage CubeMapEditorImage::getImage() const
{
    return image;
}

void CubeMapEditorImage::setFocus(double zoom, QPointF offset)
{
    this->zoom = zoom;
    this->offset = offset;
}

void CubeMapEditorImage::rotate()
{
    rotation = (rotation+1)%4;
}

int CubeMapEditorImage::getRotation()
{
    return rotation;
}

void CubeMapEditorImage::bindTexture()
{
    if (have_image)
        texture->bind();
}

QString CubeMapEditorImage::getPath() const
{
    return this->path;
}

void CubeMapEditorImage::getFocus(double& zoom, QPointF& offset) const
{
    zoom = this->zoom;
    offset = this->offset;
}
