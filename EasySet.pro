#-------------------------------------------------
#
# Project created by QtCreator 2014-12-30T21:22:18
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = EasySet
TEMPLATE = app
CONFIG += c++11

RC_FILE = resources/resources.rc

INCLUDEPATH += src/

SOURCES +=\
    src/main.cpp \
    src/window.cpp \
    src/card.cpp \
    src/cardwidget.cpp \
    src/controller.cpp \
    src/client.cpp \
    src/player.cpp \
    src/packethandler.cpp \
    src/server.cpp \
    src/informationwidget.cpp \
    src/setupwindow.cpp

HEADERS  += \
    src/window.hpp \
    src/card.hpp \
    src/cardwidget.hpp \
    src/enums.hpp \
    src/controller.hpp \
    src/client.hpp \
    src/player.hpp \
    src/packethandler.hpp \
    src/server.hpp \
    src/informationwidget.hpp \
    src/setupwindow.hpp

FORMS    += \
    forms/window.ui \
    forms/setupwindow.ui
