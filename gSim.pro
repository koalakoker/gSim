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
        qcustomplot.cpp \
    wscope.cpp \
    mainsimulator.cpp \
    mathfunction.cpp \
    waxisctrl.cpp \
    wcursorctrl.cpp \
    sinfunction.cpp

HEADERS  += gsim.h \
        qcustomplot.h \
    wscope.h \
    mainsimulator.h \
    mathfunction.h \
    waxisctrl.h \
    wcursorctrl.h \
    sinfunction.h

FORMS    += gsim.ui \
    wscope.ui \
    waxisctrl.ui \
    wcursorctrl.ui

DISTFILES +=

RESOURCES += \
    resource.qrc
