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

SOURCES += main.cpp\
        mainwindow.cpp \
    server.cpp \
    client.cpp \
    packetadministration.cpp

HEADERS  += mainwindow.h \
    server.h \
    client.h \
    packetadministration.h

FORMS    += mainwindow.ui
