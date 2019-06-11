#-------------------------------------------------
#
# Project created by QtCreator 2019-03-20T21:00:47
#
#-------------------------------------------------

QT       += opengl core gui widgets 3dcore 3drender 3dinput 3dlogic 3dextras 3danimation printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Physics
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

CONFIG += c++11 resources_big static


QMAKE_CXXFLAGS_RELEASE -= -O2

FORMS += \
    help.ui \
    mainwindow.ui \
    plot.ui

HEADERS += \
    Camera.h \
    bullet.h \
    help.h \
    laboratory.h \
    mainwindow.h \
    materialpoint.h \
    measurer.h \
    object.h \
    pendulum.h \
    physics.h \
    plot.h \
    qcustomplot.h

SOURCES += \
    Camera.cpp \
    bullet.cpp \
    help.cpp \
    laboratory.cpp \
    main.cpp \
    mainwindow.cpp \
    materialpoint.cpp \
    measurer.cpp \
    object.cpp \
    pendulum.cpp \
    plot.cpp \
    qcustomplot.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc

win32:RC_ICONS = res/ico.ico
