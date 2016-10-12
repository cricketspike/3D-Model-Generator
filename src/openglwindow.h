// Nir Jacobson
// njacobs1@ucsc.edu
// 2016-10-06
// Adapted from: http://doc.qt.io/qt-5/qtgui-openglwindow-example.html

#ifndef OPENGLWINDOW_H
#define OPENGLWINDOW_H

#include <QWindow>
#include <QOpenGLFunctions>
#include <QOpenGLPaintDevice>
#include <QPainter>
#include <QCoreApplication>

class OpenGLWindow : public QWindow, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    explicit OpenGLWindow(QWindow* parent = 0);
    ~OpenGLWindow();

    virtual void initialize();                  // Create shader program, link, get attrs/uniforms, etc.
    virtual void render();                      // 3D rendering

public slots:
    void renderLater();                         // Queue an event that renderNow() should get called
    void renderNow();                           // Initialize OpenGL if not already, then render() and display

protected:
    bool event(QEvent* event) Q_DECL_OVERRIDE;              // Intercepts window events to handle renderLater()'s
    void exposeEvent(QExposeEvent* event) Q_DECL_OVERRIDE;  // On-screen window visibility has changed, re-render

private:
    bool m_update_pending;                      // renderLater() called but event not yet processed?

    QOpenGLContext* m_context;                  // OpenGL context pointer
};

#endif // OPENGLWINDOW_H
