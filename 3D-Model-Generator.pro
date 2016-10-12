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
    src/main.cpp

HEADERS += \
    src/openglwindow.h \
    src/mainwaindow.h
