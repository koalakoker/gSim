#-------------------------------------------------
#
# Project created by QtCreator 2017-08-13T16:38:16
#
#-------------------------------------------------

QT       += widgets printsupport

TARGET = simModules
TEMPLATE = lib

DEFINES += SIMMODULES_LIBRARY

INCLUDEPATH += simModules/inc

SOURCES +=  \
            simModules/src/sdata.cpp \
            simModules/src/sdatavector.cpp \
            simModules/src/selement.cpp \
            simModules/src/ssource.cpp \
            simModules/src/ssink.cpp \
            simModules/src/ssscope.cpp \
            simModules/src/sssincos.cpp \
            simModules/src/stransfer.cpp \
            simModules/src/staritmetic.cpp \
            simModules/src/stransferbinary.cpp \
            simModules/src/stmux.cpp \
            simModules/src/stdemux.cpp \
            simModules/src/ssramp.cpp \
            simModules/src/stprev.cpp \
            simModules/src/stpi.cpp \
            simModules/src/strl.cpp \
            simModules/src/stdpi.cpp \
            simModules/src/stpid.cpp \
            simModules/src/stfdiscretefirstorder.cpp \
            simModules/src/stfintegrator.cpp \
            simModules/src/stfderivatorfitered.cpp \
            simModules/src/stdqtoabc.cpp \
            simModules/src/stpmsmabc.cpp \
            simModules/src/stpmsmdq.cpp \
            simModules/src/stabctodq.cpp \
            simModules/src/pmsmvars.cpp \
            simModules/src/motormechvars.cpp \
            simModules/src/smotor.cpp \
            simModules/src/smotormech.cpp \
            simModules/src/stdqtoalphabeta.cpp \
            simModules/src/svm.cpp \
            simModules/src/stsvm.cpp \
            simModules/src/qcustomplot.cpp \
            simModules/src/wscope.cpp \
            simModules/src/waxisctrl.cpp \
            simModules/src/wcursorctrl.cpp \

HEADERS += \
            simModules/inc/simmodules_global.h \
            simModules/inc/sdata.h \
            simModules/inc/sdatavector.h \
            simModules/inc/selement.h \
            simModules/inc/ssource.h \
            simModules/inc/ssink.h \
            simModules/inc/ssscope.h \
            simModules/inc/sssincos.h \
            simModules/inc/stransfer.h \
            simModules/inc/staritmetic.h \
            simModules/inc/stransferbinary.h \
            simModules/inc/stmux.h \
            simModules/inc/stdemux.h \
            simModules/inc/ssramp.h \
            simModules/inc/stprev.h \
            simModules/inc/stpi.h \
            simModules/inc/strl.h \
            simModules/inc/stdpi.h \
            simModules/inc/stpid.h \
            simModules/inc/stfdiscretefirstorder.h \
            simModules/inc/stfintegrator.h \
            simModules/inc/discretetimetransformtype.h \
            simModules/inc/stfderivatorfitered.h \
            simModules/inc/stdqtoabc.h \
            simModules/inc/stpmsmabc.h \
            simModules/inc/stpmsmdq.h \
            simModules/inc/stabctodq.h \
            simModules/inc/pmsmvars.h \
            simModules/inc/motormechvars.h \
            simModules/inc/smotor.h \
            simModules/inc/smotormech.h \
            simModules/inc/stdqtoalphabeta.h \
            simModules/inc/svm.h \
            simModules/inc/stsvm.h \
            simModules/inc/qcustomplot.h \
            simModules/inc/wscope.h \
            simModules/inc/waxisctrl.h \
            simModules/inc/wcursorctrl.h \

FORMS    += simModules/src/wscope.ui \
            simModules/src/waxisctrl.ui \
            simModules/src/wcursorctrl.ui \

RESOURCES += \
    resource.qrc

unix {
    target.path = /usr/lib
    INSTALLS += target
}
