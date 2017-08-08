#ifndef GSIM_H
#define GSIM_H

#include <QMainWindow>
#include "simulationTemplates/baseSimulationModel.h"
#include "simulationTemplates/baseSimulationView.h"

#include "simulationTemplates/simulationModel0.h"

#include <QTimer>

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

private:
    Ui::gSim *ui;

    baseSimulationModel* m_simModel;
    baseSimulationView* m_simView;
    QWidget* m_lastSetWidget;

    simulationModel0 m_simModel0;

    void setSimulation(void);

    QTimer testTim;

};

#endif // GSIM_H
