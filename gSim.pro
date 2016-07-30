#-------------------------------------------------
#
# Project created by QtCreator 2016-07-29T07:03:34
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = gSim
TEMPLATE = app


SOURCES += main.cpp\
        gsim.cpp \
    qcustomplot/qcustomplot.cpp

HEADERS  += gsim.h \
    qcustomplot/qcustomplot.h

FORMS    += gsim.ui
