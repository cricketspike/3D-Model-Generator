QT += core
QT += gui
QT += widgets

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
    src/Display.cpp \
    src/Texture.cpp \
    src/Shader.cpp \
    src/stb_image.c \
    src/Mesh.cpp

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
    src/Display.h \
    src/stb_image.h \
    src/Texture.h \
    src/Shader.h \
    src/Transform.h \
    src/Mesh.h

RESOURCES += \
    resources/resources.qrc
