#include "simulationmanager.h"
#include "ui_simulationmanager.h"
#include "simModel/inc/simModel.h"
#include "simModel/inc/simModelTest.h"

#include <QtDebug>

SimulationManager::SimulationManager(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SimulationManager)
{
    ui->setupUi(this);

    // Add here any model
    simModel* m = new simModel();
    smList.append(m);

    simModelTest* m1 = new simModelTest();
    smList.append(m1);

    for (int i = 0; i < smList.count(); i++)
    {
        ui->simList->addItem(smList.at(i)->m_description);
    }
}

SimulationManager::~SimulationManager()
{
    delete ui;
}

void SimulationManager::on_actionRun_triggered()
{
    // Run selected simulation
    int sel = ui->simList->currentRow();
    if (sel > -1)
    {
        runSimulation(sel);
    }
}

void SimulationManager::on_pushButton_clicked()
{
    // Push button -> same as actionRun
    on_actionRun_triggered();
}

void SimulationManager::on_simList_itemDoubleClicked(QListWidgetItem *item)
{
    // Double click on simulation -> same as actionRun
    int sel = ui->simList->row(item);
    if (sel > -1)
    {
        runSimulation(sel);
    }
}

void SimulationManager::runSimulation(int i)
{
    baseSimModel* sm = smList.at(i);

    commonSimView* sw = new commonSimView();
    sw->setSimModel(sm);
    sw->updateView();

    gSim* gs = new gSim();
    gs->setSimModel(sm);
    gs->setSimView(sw);

    gsList.append(gs);
    gs->show();
}

void SimulationManager::closeEvent(QCloseEvent *event)
{
    for (int i = 0; i < gsList.count(); i++)
    {
        gsList.at(i)->close();
    }
    event->accept();
}
