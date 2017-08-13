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
    wscope/waxisctrl.cpp \
    wscope/wcursorctrl.cpp \
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
    simTemplates/simModel/baseSimModel.cpp \
    simTemplates/simModel/simModel0.cpp \
    simTemplates/simModel/simModel1.cpp \
    simTemplates/simModel/simModel2.cpp \
    simTemplates/simModel/simModel3.cpp \
    simTemplates/simModel/simModel4.cpp \
    simTemplates/simModel/simModel5.cpp \
    simTemplates/simModel/simModel6.cpp \
    simTemplates/simModel/simModel7.cpp \
    simTemplates/simModel/simModel8.cpp \
    simTemplates/simModel/simModel9.cpp \
    simTemplates/simView/baseSimView.cpp \
    simTemplates/simView/simView7.cpp \
    simTemplates/simView/simView8.cpp \
    simTemplates/simModel/simModelElement.cpp \
    simTemplates/simView/commonSimView.cpp

HEADERS  += gsim.h \
    qcustomplot.h \
    wscope/wscope.h \
    wscope/waxisctrl.h \
    wscope/wcursorctrl.h \
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
    simTemplates/simModel/baseSimModel.h \
    simTemplates/simModel/simModel0.h \
    simTemplates/simModel/simModel1.h \
    simTemplates/simModel/simModel2.h \
    simTemplates/simModel/simModel3.h \
    simTemplates/simModel/simModel4.h \
    simTemplates/simModel/simModel5.h \
    simTemplates/simModel/simModel6.h \
    simTemplates/simModel/simModel7.h \
    simTemplates/simModel/simModel8.h \
    simTemplates/simModel/simModel9.h \
    simTemplates/simView/baseSimView.h \
    simTemplates/simView/simView7.h \
    simTemplates/simView/simView8.h \
    simTemplates/simModel/simModelElement.h \
    simTemplates/simView/commonSimView.h

FORMS    += gsim.ui \
    wscope/wscope.ui \
    wscope/waxisctrl.ui \
    wscope/wcursorctrl.ui \
    simTemplates/simView/baseSimView.ui \
    simTemplates/simView/simView7.ui \
    simTemplates/simView/simView8.ui

RESOURCES += \
    resource.qrc

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../build-gSimModel/release/ -lgSimModel
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../build-gSimModel/debug/ -lgSimModel
else:unix: LIBS += -L$$PWD/../build-gSimModel/ -lgSimModel

INCLUDEPATH += $$PWD/simModel
DEPENDPATH += $$PWD/simModel
