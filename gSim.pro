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
    wscope/wscope.cpp \
    mainsimulator.cpp \
    mathfunction.cpp \
    wscope/waxisctrl.cpp \
    wscope/wcursorctrl.cpp \
    sinfunction.cpp \
    simulation/sdata.cpp \
    simulation/sdatavector.cpp \
    simulation/selement.cpp \
    simulation/ssource.cpp \
    simulation/ssink.cpp \
    simulation/ssscope.cpp \
    simulation/sssincos.cpp \
    simulation/stransfer.cpp \
    simulation/staritmetic.cpp \
    simulation/stransferbinary.cpp \
    simulation/stmux.cpp \
    simulation/stdemux.cpp

HEADERS  += gsim.h \
        qcustomplot.h \
    wscope/wscope.h \
    mainsimulator.h \
    mathfunction.h \
    wscope/waxisctrl.h \
    wscope/wcursorctrl.h \
    sinfunction.h \
    simulation/sdata.h \
    simulation/sdatavector.h \
    simulation/selement.h \
    simulation/ssource.h \
    simulation/ssink.h \
    simulation/ssscope.h \
    simulation/sssincos.h \
    simulation/stransfer.h \
    simulation/staritmetic.h \
    simulation/stransferbinary.h \
    simulation/stmux.h \
    simulation/stdemux.h

FORMS    += gsim.ui \
    wscope/wscope.ui \
    wscope/waxisctrl.ui \
    wscope/wcursorctrl.ui

DISTFILES +=

RESOURCES += \
    resource.qrc
