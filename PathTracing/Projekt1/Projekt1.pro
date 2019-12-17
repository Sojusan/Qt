#-------------------------------------------------
#
# Project created by QtCreator 2019-02-27T14:39:56
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Projekt1
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
    camera.cpp \
    constanttexture.cpp \
    dielectric.cpp \
    diffuselight.cpp \
    flipnormals.cpp \
    hitable.cpp \
    hitablelist.cpp \
    lambertian.cpp \
        main.cpp \
        mainwindow.cpp \
    material.cpp \
    metal.cpp \
    mywidget.cpp \
    ray.cpp \
    sphere.cpp \
    texture.cpp \
    xyrect.cpp \
    xzrect.cpp \
    yzrect.cpp

HEADERS += \
    camera.h \
    constanttexture.h \
    dielectric.h \
    diffuselight.h \
    flipnormals.h \
    hitable.h \
    hitablelist.h \
    lambertian.h \
        mainwindow.h \
    material.h \
    metal.h \
    mywidget.h \
    ray.h \
    sphere.h \
    texture.h \
    xyrect.h \
    xzrect.h \
    yzrect.h

FORMS += \
        mainwindow.ui

LIBS += -llapack -lblas -larmadillo

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
