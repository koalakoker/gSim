#ifndef GSIM_H
#define GSIM_H

#include <QMainWindow>
#include "simulationTemplates/baseSimulationModel.h"
#include "simulationTemplates/baseSimulationView.h"

#include "simulationTemplates/simulationModel0.h"
#include "simulationTemplates/simulationModel1.h"
#include "simulationTemplates/simulationModel2.h"
#include "simulationTemplates/simulationModel3.h"
#include "simulationTemplates/simulationModel4.h"
#include "simulationTemplates/simulationModel5.h"
#include "simulationTemplates/simulationModel6.h"

#include "simulationTemplates/simulationModel7.h"
#include "simulationTemplates/simulationView7.h"

#include "simulationTemplates/simulationModel8.h"
#include "simulationTemplates/simulationView8.h"

#include "simulationTemplates/simulationModel9.h"
#include "simulationTemplates/simulationView9.h"

#include <QTimer>
//#define TEST
#define SIM_TEST 100
#define MAX_TEST_NUM 12

namespace Ui {
class gSim;
}

class gSim : public QMainWindow
{
    Q_OBJECT

public:
    explicit gSim(QWidget *parent = 0);
    ~gSim();

private slots:
    void on_startSimulation_clicked();
    void updateProgress(double percentage);

    void on_simulation_valueChanged(int arg1);
    void testTimeout(void);

private:
    Ui::gSim *ui;

    baseSimulationModel* m_simModel;
    baseSimulationView* m_simView;
    QWidget* m_lastSetWidget;

    simulationModel0 m_simModel0;
    simulationModel1 m_simModel1;
    simulationModel2 m_simModel2;
    simulationModel3 m_simModel3;
    simulationModel4 m_simModel4;
    simulationModel5 m_simModel5;
    simulationModel6 m_simModel6;
    simulationModel7 m_simModel7;
    simulationModel8 m_simModel8;
    simulationModel9 m_simModel9;
    simulationView7  m_simView7;
    simulationView8  m_simView8;
    simulationView9  m_simView9;

    void setSimulation(int arg);

    QTimer testTim;

};

#endif // GSIM_H
