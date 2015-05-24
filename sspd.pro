#-------------------------------------------------
#
# Project created by QtCreator 2015-05-20T18:09:27
#
#-------------------------------------------------

QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = sspd
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    klasy/koordynator.cpp \
    klasy/zlecenie.cpp \
    qcustomplot/qcustomplot.cpp

HEADERS  += mainwindow.h \
    dummy.h \
    klasy/koordynator.h \
    klasy/zlecenie.h \
    qcustomplot/qcustomplot.h

FORMS    += mainwindow.ui

CONFIG += c++11

