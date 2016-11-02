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
    src/stb_image.c

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
    src/stb_image.h

RESOURCES += \
    resources/resources.qrc
INCLUDEPATH += "C:/Qt/5.6/msvc2015_64/include/"

unix|win32: LIBS += -lopengl32 -lglew32 -lglew32s -lSDL2 -lSDL2main -lSDL2test
INCLUDEPATH += $$PWD/include
DEPENDPATH += $$PWD/include
