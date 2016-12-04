#ifndef GSIM_H
#define GSIM_H

#include <QMainWindow>
#include "simulationTemplates/baseSimulationModel.h"
#include "simulationTemplates/baseSimulationView.h"

#include <QTimer>
#define SIM_TEST 100

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

    // Test
    void testTimeout(void);

private:
    Ui::gSim *ui;

    baseSimulationModel* m_simModel;
    baseSimulationView* m_simView;

    void setSimulation(int arg);

    // Test
    QTimer testTim;

};

#endif // GSIM_H
