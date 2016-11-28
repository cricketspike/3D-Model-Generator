#include "cubemapeditorimage.h"
#include <iostream>
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

void CubeMapEditorImage::setTmpPath(QString path)
{
    this->tmpPath = path;
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

    weight = std::vector<std::vector<uint8_t>>();

    //Go through every pixel in the picture
    for ( int col = 0; col < image.width(); ++col ) {

      weight.push_back(std::vector<uint8_t>());
      for ( int row = 0; row < image.height(); ++row ) {
        uint8_t data = 0;
        weight[col].push_back(data);
      }
    }
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

QString CubeMapEditorImage::getTmpPath() const
{
    return this->tmpPath;
}

void CubeMapEditorImage::getFocus(double& zoom, QPointF& offset) const
{
    zoom = this->zoom;
    offset = this->offset;
}

void CubeMapEditorImage::addWeight(double x, double y) {
    std::cout << x << " " << y << std::endl;
    if (weight[x].at(y) < 100) {
        weight[x].at(y) += 1;
    }
    std::cout << (int) weight[x].at(y) << std::endl;
}

void CubeMapEditorImage::subtractWeight(double x, double y) {
    std::cout << x << " " << y << std::endl;
    if (weight[x].at(y) > 0) {
        weight[x].at(y) -= 1;
    }
    std::cout << (int) weight[x].at(y) << std::endl;

}
