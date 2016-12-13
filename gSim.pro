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
    mathfunction.cpp \
    sinfunction.cpp \
    wscope/wscope.cpp \
    wscope/waxisctrl.cpp \
    wscope/wcursorctrl.cpp \
    simulationModules/sdata.cpp \
    simulationModules/sdatavector.cpp \
    simulationModules/selement.cpp \
    simulationModules/ssource.cpp \
    simulationModules/ssink.cpp \
    simulationModules/ssscope.cpp \
    simulationModules/sssincos.cpp \
    simulationModules/stransfer.cpp \
    simulationModules/staritmetic.cpp \
    simulationModules/stransferbinary.cpp \
    simulationModules/stmux.cpp \
    simulationModules/stdemux.cpp \
    simulationModules/ssramp.cpp \
    simulationModules/stprev.cpp \
    simulationModules/stpi.cpp \
    simulationModules/strl.cpp \
    simulationModules/stdpi.cpp \
    simulationModules/stpid.cpp \
    simulationModules/stfdiscretefirstorder.cpp \
    simulationModules/stfintegrator.cpp \
    simulationModules/stfderivatorfitered.cpp \
    simulationModules/stdqtoabc.cpp \
    simulationModules/stpmsmabc.cpp \
    simulationModules/stpmsmdq.cpp \
    simulationModules/stabctodq.cpp \
    simulationModules/pmsmvars.cpp \
    simulationModules/smotor.cpp \
    simulationModules/stdqtoalphabeta.cpp \
    simulationModules/svm.cpp \
    simulationModules/stsvm.cpp \
    simulationTemplates/baseSimualtionView.cpp \
    simulationTemplates/baseSimulationModel.cpp \
    simulationTemplates/simulationModel8.cpp \
    simulationTemplates/simulationView8.cpp \
    simulationTemplates/simulationModel7.cpp \
    simulationTemplates/simulationView7.cpp \
    simulationTemplates/simulationModel0.cpp \
    simulationTemplates/simulationModel1.cpp \
    simulationTemplates/simulationModel2.cpp \
    simulationTemplates/simulationModel3.cpp \
    simulationTemplates/simulationModel4.cpp \
    simulationTemplates/simulationModel5.cpp \
    simulationTemplates/simulationModel6.cpp \
    simulationModules/motormechvars.cpp \
    simulationModules/stmotormech.cpp \
    simulationModules/stdelay.cpp

HEADERS  += gsim.h \
    qcustomplot.h \
    mathfunction.h \
    sinfunction.h \
    wscope/wscope.h \
    wscope/waxisctrl.h \
    wscope/wcursorctrl.h \
    simulationModules/sdata.h \
    simulationModules/sdatavector.h \
    simulationModules/selement.h \
    simulationModules/ssource.h \
    simulationModules/ssink.h \
    simulationModules/ssscope.h \
    simulationModules/sssincos.h \
    simulationModules/stransfer.h \
    simulationModules/staritmetic.h \
    simulationModules/stransferbinary.h \
    simulationModules/stmux.h \
    simulationModules/stdemux.h \
    simulationModules/ssramp.h \
    simulationModules/stprev.h \
    simulationModules/stpi.h \
    simulationModules/strl.h \
    simulationModules/stdpi.h \
    simulationModules/stpid.h \
    simulationModules/stfdiscretefirstorder.h \
    simulationModules/stfintegrator.h \
    simulationModules/discretetimetransformtype.h \
    simulationModules/stfderivatorfitered.h \
    simulationModules/stdqtoabc.h \
    simulationModules/stpmsmabc.h \
    simulationModules/stpmsmdq.h \
    simulationModules/stabctodq.h \
    simulationModules/pmsmvars.h \
    simulationModules/smotor.h \
    simulationModules/stdqtoalphabeta.h \
    simulationModules/svm.h \
    simulationModules/stsvm.h \
    simulationTemplates/baseSimulationModel.h \
    simulationTemplates/baseSimulationView.h \
    simulationTemplates/simulationModel8.h \
    simulationTemplates/simulationView8.h \
    simulationTemplates/simulationModel7.h \
    simulationTemplates/simulationView7.h \
    simulationTemplates/simulationModel0.h \
    simulationTemplates/simulationModel1.h \
    simulationTemplates/simulationModel2.h \
    simulationTemplates/simulationModel3.h \
    simulationTemplates/simulationModel4.h \
    simulationTemplates/simulationModel5.h \
    simulationTemplates/simulationModel6.h \
    simulationModules/motormechvars.h \
    simulationModules/stmotormech.h \
    simulationModules/stdelay.h

FORMS    += gsim.ui \
    wscope/wscope.ui \
    wscope/waxisctrl.ui \
    wscope/wcursorctrl.ui \
    simulationTemplates/simulationView8.ui \
    simulationTemplates/baseSimulationView.ui \
    simulationTemplates/simulationView7.ui

RESOURCES += \
    resource.qrc
