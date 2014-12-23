#-------------------------------------------------
#
# Project created by QtCreator 2014-12-04T14:10:12
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Set
TEMPLATE = app

INCLUDEPATH +=  include/data \
                src/data

SOURCES +=\
    src/data/card.cpp \
    src/data/main.cpp \
    src/data/controller.cpp \
    src/data/window.cpp

HEADERS  += \
    include/data/card.h \
    include/data/controller.h \
    include/data/window.h

FORMS    += \
    forms/window.ui
