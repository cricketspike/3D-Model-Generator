#ifndef CUBEMAPEDITORIMAGE_H
#define CUBEMAPEDITORIMAGE_H

#include <QObject>
#include <QOpenGLTexture>


/*
 * This class contains the image and editing state of one face
 * of the cube map in CubeMapEditor.
 *
 */

class CubeMapEditorImage : public QObject
{
    Q_OBJECT
public:
    explicit CubeMapEditorImage(QObject *parent = 0);
    ~CubeMapEditorImage();

    QString getPath() const;
    QString getTmpPath() const;
    void setPath(QString path);
    void setTmpPath(QString path);
    void setImage(QImage image);
    bool haveImage() const;
    QImage getImage() const;
    void addWeight(double x, double y);
    void subtractWeight(double x, double y);

    // Focus: positioning & scaling/zoom
    void getFocus(double& zoom, QPointF& offset) const;
    void setFocus(double zoom, QPointF offset);

    void rotate();
    int getRotation();

    void bindTexture();

private:
    // Image path
    QString path;
    QString tmpPath;
    // Image
    bool have_image;
    QImage image;
    QOpenGLTexture* texture;

    // Focus
    double zoom;
    QPointF offset;

    int rotation;
    std::vector<std::vector<uint8_t>> weight;

signals:

public slots:
};

#endif // CUBEMAPEDITORIMAGE_H
