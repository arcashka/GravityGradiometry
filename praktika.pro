#-------------------------------------------------
#
# Project created by QtCreator 2016-12-28T22:27:02
#
#-------------------------------------------------

QT       += core gui
QT       += core gui opengl
QT       += opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = praktika
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

QMAKE_LIBS += opengl32.lib

SOURCES += areaSrc/area.cpp \
    areaSrc/cube.cpp \
    areaSrc/receiver.cpp \
    areaSrc/subdomain.cpp \
    directTaskSrc/directtask.cpp \
    guiSrc/mainwindow.cpp \
    guiSrc/widget3d.cpp \
    guiSrc/widget3dsecond.cpp \
    inverseTaskSrc/inversetask.cpp \
    guiSrc/main.cpp

HEADERS  += directTaskHeaders/directtask.h \
    areaHeaders/receiver.h \
    areaHeaders/areaproperties.h \
    areaHeaders/area.h \
    areaHeaders/cube.h \
    areaHeaders/receiver.h \
    areaHeaders/subdomain.h \
    directTaskHeaders/directtask.h \
    guiHeaders/widget3dsecond.h \
    guiHeaders/mainwindow.h \
    guiHeaders/widget3d.h \
    inverseTaskHeaders/inversetask.h \
    inverseTaskHeaders/inversetaskproperties.h \
    Utility/Index3d.h

FORMS    += mainwindow.ui

DISTFILES +=
