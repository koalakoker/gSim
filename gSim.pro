#-------------------------------------------------
#
# Project created by QtCreator 2016-07-29T07:03:34
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = gSim
TEMPLATE = app

INCLUDEPATH += \
    simModules/inc\
    simModules/inc/plot\
    simModel/inc

SOURCES += \
    main.cpp\
    gsim.cpp \
    simTemplates/simView/baseSimView.cpp \
    simTemplates/simView/commonSimView.cpp \
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
    simModel/src/simModel.cpp \
    simModel/src/baseSimModel.cpp \
    simModel/src/simModelElement.cpp \
    wplot/axis.cpp \
    wplot/axisproperties.cpp \
    wplot/cursor.cpp \
    wplot/curve.cpp \
    wplot/iconcursors.cpp \
    wplot/jsonserial.cpp \
    wplot/plotter.cpp \
    wplot/state/hzoomstate.cpp \
    wplot/state/normalstate.cpp \
    wplot/state/state.cpp \
    wplot/state/vzoomstate.cpp \
    wplot/state/zoomstate.cpp \
    wplot/wplot.cpp \
    wplot/zoom.cpp

HEADERS += \
    gsim.h \
    simTemplates/simView/baseSimView.h \
    simTemplates/simView/commonSimView.h \
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
    simModel/inc/simModel.h \
    simModel/inc/gsimmodel_global.h \
    simModel/inc/baseSimModel.h \
    simModel/inc/simModelElement.h \
    wplot/axis.h \
    wplot/axisproperties.h \
    wplot/cursor.h \
    wplot/curve.h \
    wplot/iconcursors.h \
    wplot/jsonserial.h \
    wplot/plotter.h \
    wplot/state/hzoomstate.h \
    wplot/state/normalstate.h \
    wplot/state/state.h \
    wplot/state/vzoomstate.h \
    wplot/state/zoomstate.h \
    wplot/wplot.h \
    wplot/zoom.h

FORMS += \
    gsim.ui \
    simTemplates/simView/baseSimView.ui

RESOURCES += \
    wplot/resource.qrc

DISTFILES += \
    wplot/png/icons8-zoom-in-24.png \
    wplot/png/icons8-zoom-in-30.png \
    wplot/png/icons8-zoom-out-24.png
