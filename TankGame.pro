#-------------------------------------------------
#
# Project created by QtCreator 2018-04-05T08:42:52
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TankGame
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


SOURCES += \
        main.cpp \
        gamewindow.cpp \
    gamewidget.cpp \
    mapdata.cpp \
    settings.cpp \
    filltype.cpp \
    game.cpp \
    tanktype.cpp \
    direction.cpp \
    tank.cpp \
    bullet.cpp \
    scorewidget.cpp

HEADERS += \
        gamewindow.h \
    gamewidget.h \
    mapdata.h \
    settings.h \
    filltype.h \
    game.h \
    tanktype.h \
    direction.h \
    tank.h \
    bullet.h \
    scorewidget.h

FORMS += \
        gamewindow.ui \
    gamewidget.ui \
    scorewidget.ui

RESOURCES += \
    resource.qrc
