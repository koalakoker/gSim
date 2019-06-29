#ifndef SIMULATIONMANAGER_H
#define SIMULATIONMANAGER_H

#include <QMainWindow>
#include <QListWidget>

#include "gsim.h"
#include "simTemplates/simView/commonSimView.h"
#include "simModel/inc/baseSimModel.h"

namespace Ui {
class SimulationManager;
}

class SimulationManager : public QMainWindow
{
    Q_OBJECT

public:
    explicit SimulationManager(QWidget *parent = nullptr);
    ~SimulationManager();

private slots:
    void on_actionRun_triggered();
    void on_pushButton_clicked();
    void on_simList_itemDoubleClicked(QListWidgetItem *item);

private:
    Ui::SimulationManager *ui;
    QList<gSim*> gsList;
    QList<baseSimModel*> smList;

private:
    void runSimulation(int i);
    void closeEvent(QCloseEvent *event);
};

#endif // SIMULATIONMANAGER_H
