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

INCLUDEPATH +=  include/network \
                src/network

SOURCES +=\
    src/network/client.cpp \
    src/network/main.cpp \
    src/network/mainwindow.cpp \
    src/network/packetadministration.cpp \
    src/network/server.cpp

HEADERS  += \
    include/network/client.h \
    include/network/mainwindow.h \
    include/network/packetadministration.h \
    include/network/server.h

FORMS    += mainwindow.ui
