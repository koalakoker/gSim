#ifndef GSIM_H
#define GSIM_H

#include <QMainWindow>
#include "simulationTemplates/baseSimulationModel.h"
#include "simulationTemplates/baseSimulationView.h"

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

private:
    Ui::gSim *ui;

    baseSimulationModel* m_simModel;
    baseSimulationView* m_simView;

    QWidget* lastSetWidget;

    void setSimulation(int arg);

};

#endif // GSIM_H
