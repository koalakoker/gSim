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
    simulationTemplates/simModel/baseSimulationModel.cpp \
    simulationTemplates/simModel/simulationModel0.cpp \
    simulationTemplates/simModel/simulationModel1.cpp \
    simulationTemplates/simModel/simulationModel2.cpp \
    simulationTemplates/simModel/simulationModel3.cpp \
    simulationTemplates/simModel/simulationModel4.cpp \
    simulationTemplates/simModel/simulationModel5.cpp \
    simulationTemplates/simModel/simulationModel6.cpp \
    simulationTemplates/simModel/simulationModel7.cpp \
    simulationTemplates/simModel/simulationModel8.cpp \
    simulationTemplates/simView/baseSimualtionView.cpp \
    simulationTemplates/simView/simulationView7.cpp \
    simulationTemplates/simView/simulationView8.cpp

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
    simulationTemplates/simModel/baseSimulationModel.h \
    simulationTemplates/simModel/simulationModel0.h \
    simulationTemplates/simModel/simulationModel1.h \
    simulationTemplates/simModel/simulationModel2.h \
    simulationTemplates/simModel/simulationModel3.h \
    simulationTemplates/simModel/simulationModel4.h \
    simulationTemplates/simModel/simulationModel5.h \
    simulationTemplates/simModel/simulationModel6.h \
    simulationTemplates/simModel/simulationModel7.h \
    simulationTemplates/simModel/simulationModel8.h \
    simulationTemplates/simView/baseSimulationView.h \
    simulationTemplates/simView/simulationView7.h \
    simulationTemplates/simView/simulationView8.h

FORMS    += gsim.ui \
    wscope/wscope.ui \
    wscope/waxisctrl.ui \
    wscope/wcursorctrl.ui \
    simulationTemplates/simView/baseSimulationView.ui \
    simulationTemplates/simView/simulationView7.ui \
    simulationTemplates/simView/simulationView8.ui

RESOURCES += \
    resource.qrc
