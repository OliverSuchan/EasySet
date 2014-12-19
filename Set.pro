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

SOURCES +=\
    src/client.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/packetadministration.cpp \
    src/server.cpp

HEADERS  += \
    include/client.h \
    include/mainwindow.h \
    include/packetadministration.h \
    include/server.h

FORMS    += mainwindow.ui
