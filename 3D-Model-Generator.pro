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
    src/ColoredVertexMatrix.cpp \
    src/votingmatrix.cpp \
    src/main.cpp \
    src/ImportedImage.cpp \
    src/nullify.cpp \
    src/vertexlinker.cpp

HEADERS += \
    src/openglwindow.h \
    src/mainwaindow.h \
    src/ColoredVertex.h \
    src/MatrixNode.h \
    src/ColoredVertexMatrix.h \
    src/VotingMatrix.h \
    src/ImportedImage.h \
    src/vertexlinker.h \
    src/nullify.h

RESOURCES += \
    resources/resources.qrc
