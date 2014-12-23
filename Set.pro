#-------------------------------------------------
#
# Project created by QtCreator 2014-12-04T18:01:57
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Set
TEMPLATE = app

CONFIG += c++11

# Networking
#-------------------------------------------------

INCLUDEPATH +=  include/network \
                src/network

SOURCES +=\
    src/network/client.cpp \
    src/network/main.cpp \
    src/network/mainwindow.cpp \
    src/network/server.cpp \
    src/network/packethandler.cpp

HEADERS  += \
    include/network/client.h \
    include/network/mainwindow.h \
    include/network/server.h \
    include/network/packethandler.h

FORMS    += \
    forms/mainwindow.ui

#-------------------------------------------------

# Data
#-------------------------------------------------

INCLUDEPATH +=  include/data \
                src/data

SOURCES +=\
    src/data/card.cpp \
    src/data/controller.cpp \
    src/data/window.cpp

HEADERS  += \
    include/data/card.h \
    include/data/window.h \
    include/data/controller.h

FORMS += \
    forms/window.ui

#-------------------------------------------------
