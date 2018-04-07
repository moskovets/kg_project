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

LIBS += -lpthread

SOURCES += main.cpp\
        ui/mainwindow.cpp \
    ui/mygraphicview.cpp \
    ui/mycontroller.cpp \
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
    model/triangle.cpp \
    model/mesh.cpp \
    graphic/drawer3d.cpp \
    model/model.cpp \
    graphic/render.cpp \
    graphic/setdrawer.cpp \
    graphic/dimension4.cpp \
    graphic/light.cpp

HEADERS  += ui/mainwindow.h \
    ui/mygraphicview.h \
    ui/mycontroller.h \
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
    model/triangle.h \
    model/mesh.h \
    graphic/drawer3d.h \
    model/model.h \
    graphic/render.h \
    graphic/setdrawer.h \
    ringbuffer.h \
    graphic/dimension4.h \
    graphic/light.h

FORMS    += ui/mainwindow.ui \
    ui/mygraphicview.ui \
    ui/mycontroller.ui
