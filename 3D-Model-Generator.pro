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
    src/votingmatrix.cpp

HEADERS += \
    src/openglwindow.h \
    src/mainwaindow.h \
    src/ImportedImage.h \
    src/nullify.h \
    src/votingmatrix.h \
    src/vertexlinker.h \
    src/matrixnode.h \
    src/coloredvertexmatrix.h \
    src/coloredvertex.h

RESOURCES += \
    resources/resources.qrc
