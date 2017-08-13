#-------------------------------------------------
#
# Project created by QtCreator 2017-08-13T16:38:16
#
#-------------------------------------------------

QT       += widgets printsupport

TARGET = simModules
TEMPLATE = lib

DEFINES += SIMMODULES_LIBRARY

SOURCES +=  simModules/simmodules.cpp \
            simModules/sdata.cpp \
            simModules/sdatavector.cpp \
            simModules/selement.cpp \
            simModules/ssource.cpp \
            simModules/ssink.cpp \
            simModules/ssscope.cpp \
            simModules/sssincos.cpp \
            simModules/stransfer.cpp \
            simModules/staritmetic.cpp \
            simModules/stransferbinary.cpp \
            simModules/stmux.cpp \
            simModules/stdemux.cpp \
            simModules/ssramp.cpp \
            simModules/stprev.cpp \
            simModules/stpi.cpp \
            simModules/strl.cpp \
            simModules/stdpi.cpp \
            simModules/stpid.cpp \
            simModules/stfdiscretefirstorder.cpp \
            simModules/stfintegrator.cpp \
            simModules/stfderivatorfitered.cpp \
            simModules/stdqtoabc.cpp \
            simModules/stpmsmabc.cpp \
            simModules/stpmsmdq.cpp \
            simModules/stabctodq.cpp \
            simModules/pmsmvars.cpp \
            simModules/motormechvars.cpp \
            simModules/smotor.cpp \
            simModules/smotormech.cpp \
            simModules/stdqtoalphabeta.cpp \
            simModules/svm.cpp \
            simModules/stsvm.cpp \
            qcustomplot.cpp \
            wscope/wscope.cpp \
            wscope/waxisctrl.cpp \
            wscope/wcursorctrl.cpp \

HEADERS +=  simModules/simmodules.h\
            simModules/simmodules_global.h \
            simModules/sdata.h \
            simModules/sdatavector.h \
            simModules/selement.h \
            simModules/ssource.h \
            simModules/ssink.h \
            simModules/ssscope.h \
            simModules/sssincos.h \
            simModules/stransfer.h \
            simModules/staritmetic.h \
            simModules/stransferbinary.h \
            simModules/stmux.h \
            simModules/stdemux.h \
            simModules/ssramp.h \
            simModules/stprev.h \
            simModules/stpi.h \
            simModules/strl.h \
            simModules/stdpi.h \
            simModules/stpid.h \
            simModules/stfdiscretefirstorder.h \
            simModules/stfintegrator.h \
            simModules/discretetimetransformtype.h \
            simModules/stfderivatorfitered.h \
            simModules/stdqtoabc.h \
            simModules/stpmsmabc.h \
            simModules/stpmsmdq.h \
            simModules/stabctodq.h \
            simModules/pmsmvars.h \
            simModules/motormechvars.h \
            simModules/smotor.h \
            simModules/smotormech.h \
            simModules/stdqtoalphabeta.h \
            simModules/svm.h \
            simModules/stsvm.h \
            qcustomplot.h \
            wscope/wscope.h \
            wscope/waxisctrl.h \
            wscope/wcursorctrl.h \

FORMS    += wscope/wscope.ui \
    wscope/waxisctrl.ui \
    wscope/wcursorctrl.ui \

RESOURCES += \
    resource.qrc

unix {
    target.path = /usr/lib
    INSTALLS += target
}
