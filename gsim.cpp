#include <QTime>
#include "gsim.h"
#include "ui_gsim.h"
#include "simulation8.h"

gSim::gSim(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::gSim)
{
    m_sim = new simulation8(); /* Create simulation model */

    // Create all possible specific parameters to be shown in the Dyamic Layout
    sspEmpty = new SpecificSimParamsEmpty();

    sspT8 = new SpecificSimParamsTest8(); /* Create simulation view */
    sspT8->setSimulationModel(m_sim); /* Set simulation model */
    sspT8->updateView(); /* Update view values according model */

    lastSetWidget = NULL;

    ui->setupUi(this);

    ui->duration->setValue(m_sim->duration());
    ui->stepTime->setValue(m_sim->simulationTime());
    ui->controlTime->setValue(m_sim->controlTime());
    ui->simulation->setValue(m_sim->m_simulation);

    connect(m_sim, SIGNAL(updateProgress(double)), this, SLOT(updateProgress(double)));
}

gSim::~gSim()
{
    delete ui;
}

void gSim::on_startSimulation_clicked()
{
    QTime t;
    t.start();

    m_sim->setDuration(ui->duration->value());
    m_sim->setSimulationTime(ui->stepTime->value());
    m_sim->setControlTime(ui->controlTime->value());

    // Update specific params for Test 8
    sspT8->updateModel(); /* Update model before to start simulation */

    m_sim->m_simulation = ui->simulation->value();
    m_sim->startSimulation();

    ui->simInfo->setText(QString("Time elapsed: %1 s").arg((double)t.elapsed()/1000));
}

void gSim::updateProgress(double percentage)
{
    ui->progressBar->setValue(percentage * 100);
}

void gSim::on_simulation_valueChanged(int arg1)
{
    switch (arg1) {
    case 8:
        {
            updateSpecificSimParams(sspT8);
        }
        break;
    default:
    {
        updateSpecificSimParams(sspEmpty);
    }
        break;
    }
}

void gSim::updateSpecificSimParams(QWidget* newWid)
{
    if (lastSetWidget != NULL)
    {
        ui->dynamicLayout->removeWidget(lastSetWidget);
        lastSetWidget->hide();
    }
    lastSetWidget = newWid;
    ui->dynamicLayout->addWidget(lastSetWidget);
    lastSetWidget->show();
}
