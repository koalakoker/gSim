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
    simulation/stdemux.cpp \
    simulation/ssramp.cpp \
    simulation/stprev.cpp \
    simulation/stpi.cpp \
    simulation/strl.cpp \
    simulation/stdpi.cpp \
    simulation/stpid.cpp \
    simulation/stfdiscretefirstorder.cpp \
    simulation/stfintegrator.cpp \
    simulation/stfderivatorfitered.cpp \
    simulation/stdqtoabc.cpp \
    simulation/stpmsmabc.cpp \
    simulation/stpmsmdq.cpp \
    simulation/stabctodq.cpp \
    simulation/pmsmvars.cpp \
    simulation/smotor.cpp

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
    simulation/stdemux.h \
    simulation/ssramp.h \
    simulation/stprev.h \
    simulation/stpi.h \
    simulation/strl.h \
    simulation/stdpi.h \
    simulation/stpid.h \
    simulation/stfdiscretefirstorder.h \
    simulation/stfintegrator.h \
    simulation/discretetimetransformtype.h \
    simulation/stfderivatorfitered.h \
    simulation/stdqtoabc.h \
    simulation/stpmsmabc.h \
    simulation/stpmsmdq.h \
    simulation/stabctodq.h \
    simulation/pmsmvars.h \
    simulation/smotor.h

FORMS    += gsim.ui \
    wscope/wscope.ui \
    wscope/waxisctrl.ui \
    wscope/wcursorctrl.ui

DISTFILES +=

RESOURCES += \
    resource.qrc
