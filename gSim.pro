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
    wscope\wscope.cpp \
    mainsimulator.cpp \
    mathfunction.cpp \
    wscope\waxisctrl.cpp \
    wscope\wcursorctrl.cpp \
    sinfunction.cpp \
    simulation/sdata.cpp \
    simulation/sdatavector.cpp \
    simulation/selement.cpp \
    simulation/ssource.cpp \
    simulation/sssin.cpp \
    simulation/ssink.cpp \
    simulation/ssscope.cpp

HEADERS  += gsim.h \
        qcustomplot.h \
    wscope\wscope.h \
    mainsimulator.h \
    mathfunction.h \
    wscope\waxisctrl.h \
    wscope\wcursorctrl.h \
    sinfunction.h \
    simulation/sdata.h \
    simulation/sdatavector.h \
    simulation/selement.h \
    simulation/ssource.h \
    simulation/sssin.h \
    simulation/ssink.h \
    simulation/ssscope.h

FORMS    += gsim.ui \
    wscope\wscope.ui \
    wscope\waxisctrl.ui \
    wscope\wcursorctrl.ui

DISTFILES +=

RESOURCES += \
    resource.qrc
