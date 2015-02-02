#-------------------------------------------------
#
# Project created by QtCreator 2015-02-01T12:19:19
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ColorCube
TEMPLATE = app

INCLUDEPATH += "C:/Assimp-3.1.1/include"
LIBS += "C:/Assimp-3.1.1/libs/libassimp.dll"


SOURCES += main.cpp\
        MainWindow.cpp \
    Scene.cpp \
    Cube.cpp \
    LoaderOfCube.cpp

HEADERS  += MainWindow.h \
    Scene.h \
    Cube.h \
    LoaderOfCube.h

FORMS    += MainWindow.ui

RESOURCES += \
    Shaders.qrc
