QT += core
QT += gui
QT += widgets
QT += opengl
LIBS += -lopengl32

CONFIG += c++11

TARGET = 3D-Model-Generator
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += \
    src/openglwindow.cpp \
    src/mainwindow.cpp \
    src/main.cpp \
    src/nullify.cpp \
    src/importedimage.cpp \
    src/coloredvertexmatrix.cpp \
    src/vertexlinker.cpp \
    src/votingmatrix.cpp \
    src/coloredvertex.cpp \
    src/stb_image.c \
    src/vertexline.cpp \
    src/importwindow.cpp \
    src/cubepreviewwidget.cpp \
    src/cubepreviewwidgetdemo.cpp \
    src/verticessmoothing.cpp \
    src/cubemapeditordisplay.cpp \
    src/cubemapeditorimage.cpp \
    src/cubemapeditor.cpp \
<<<<<<< HEAD
    src/weighteditor.cpp
=======
    src/modelwindow.cpp \
    src/modelpreviewwidget.cpp \
    src/modeleditor.cpp \
    src/facemaker.cpp \
    src/precisetrimming.cpp
>>>>>>> master

HEADERS += \
    src/openglwindow.h \
    src/mainwaindow.h \
    src/ImportedImage.h \
    src/nullify.h \
    src/votingmatrix.h \
    src/vertexlinker.h \
    src/matrixnode.h \
    src/coloredvertexmatrix.h \
    src/coloredvertex.h \
    src/sheller.h \
    src/stb_image.h \
    src/VertexLine.h \
    src/importwindow.h \
    src/cubepreviewwidget.h \
    src/cubepreviewwidgetdemo.h \
    src/verticessmoothing.h \
    src/cubemapeditordisplay.h \
    src/cubemapeditorimage.h \
    src/cubemapeditor.h \
<<<<<<< HEAD
    src/weighteditor.h
=======
    src/modelwindow.h \
    src/modelpreviewwidget.h \
    src/modeleditor.h \
    src/facemaker.h \
    src/precisetrimming.h
>>>>>>> master

RESOURCES += \
    resources/resources.qrc
INCLUDEPATH += "C:/Qt/5.6/msvc2015_64/include/"


INCLUDEPATH += $$PWD/include
DEPENDPATH += $$PWD/include


FORMS += \
    src/importwindow.ui \
    src/cubepreviewwidgetdemo.ui \
    src/cubemapeditor.ui \
<<<<<<< HEAD
    src/weighteditor.ui
=======
    src/modelwindow.ui
>>>>>>> master
