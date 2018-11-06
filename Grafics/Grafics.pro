#-------------------------------------------------
#
# Project created by QtCreator 2017-09-23T15:16:36
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Grafics
TEMPLATE = app


SOURCES += main.cpp\
        dialog.cpp \
    animacion.cpp \
    process.cpp \
    processcontrolblock.cpp

HEADERS  += dialog.h \
    animacion.h \
    includes.h \
    process.h \
    processcontrolblock.h

FORMS    += dialog.ui

CONFIG +=c++11
QMAKE_CXXFLAGS += -std=c++11

