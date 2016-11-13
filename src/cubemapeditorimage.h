#ifndef CUBEMAPEDITORIMAGE_H
#define CUBEMAPEDITORIMAGE_H

#include <QObject>
#include <QOpenGLTexture>


/*
 * This class contains the image and editing state for one face
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
    void setPath(QString path);

    void setImage(QImage image);
    bool haveImage() const;
    QImage getImage() const;

    // Focus: positioning & scaling/zoom
    void getFocus(double& zoom, QPointF& offset) const;
    void setFocus(double zoom, QPointF offset);

    void rotate();

    void bindTexture();

private:
    // Image path
    QString path;

    // Image
    bool have_image;
    QImage image;
    QOpenGLTexture* texture;

    // Focus
    double zoom;
    QPointF offset;

signals:

public slots:
};

#endif // CUBEMAPEDITORIMAGE_H
