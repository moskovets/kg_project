#-------------------------------------------------
#
# Project created by QtCreator 2017-02-08T20:04:18
#
#-------------------------------------------------

QT       += core gui
QT       += widgets printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = laba1
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    mygraphicview.cpp \
    mycontroller.cpp \
    errors.cpp \
    CImage.cpp \
    math/quaternion.cpp \
    math/juliaset.cpp \
    juliafunctions.cpp \
    math/juliasetalgo.cpp \
    graphic/zbuffer.cpp \
    graphic/color.cpp \
    graphic/drawer.cpp \
    graphic/framebuffer.cpp \
    math/coordinates.cpp \
    math/vector4.cpp \
    math/matrix4.cpp \
    model/triangle.cpp

HEADERS  += mainwindow.h \
    mygraphicview.h \
    mycontroller.h \
    my_scene.h \
    errors.h \
    point.h \
    point.h \
    CImage.h \
    math/quaternion.h \
    math/basefunction.h \
    math/juliaset.h \
    juliafunctions.h \
    math/juliasetalgo.h \
    graphic/zbuffer.h \
    graphic/color.h \
    graphic/drawer.h \
    graphic/framebuffer.h \
    math/coordinates.h \
    math/vector4.h \
    math/matrix4.h \
    model/triangle.h

FORMS    += mainwindow.ui \
    mygraphicview.ui \
    mycontroller.ui
