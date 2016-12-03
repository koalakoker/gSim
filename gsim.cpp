#include <QTime>
#include "gsim.h"
#include "ui_gsim.h"
#include "simulationTemplates/simulationModel7.h"
#include "simulationTemplates/simulationView7.h"
#include "simulationTemplates/simulationModel8.h"
#include "simulationTemplates/simulationView8.h"

#define DEFAULT_SIMULATION 0

gSim::gSim(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::gSim)
{
    m_simModel = NULL;
    m_simView = NULL;
    lastSetWidget = NULL;

    ui->setupUi(this);

    setSimulation(DEFAULT_SIMULATION); /* To be called after UI setup */

    connect(m_simModel, SIGNAL(updateProgress(double)), this, SLOT(updateProgress(double)));
}

gSim::~gSim()
{
    delete ui;
}

void gSim::on_startSimulation_clicked()
{
    QTime t;
    t.start();

    m_simModel->setDuration(ui->duration->value());
    m_simModel->setSimulationTime(ui->stepTime->value());
    m_simModel->setControlTime(ui->controlTime->value());

    // Update specific params
    m_simView->updateModel(); /* Update model before to start simulation */

    m_simModel->m_simulation = ui->simulation->value();
    m_simModel->startSimulation();

    ui->simInfo->setText(QString("Time elapsed: %1 s").arg((double)t.elapsed()/1000));
}

void gSim::updateProgress(double percentage)
{
    ui->progressBar->setValue(percentage * 100);
}

void gSim::on_simulation_valueChanged(int arg1)
{
    setSimulation(arg1);
}

void gSim::setSimulation(int arg)
{
    bool change = true;
    if (m_simModel)
    {
        if (arg == m_simModel->m_simulation)
        {
            change = false;
        }
    }
    if (change)
    {
        if (lastSetWidget != NULL)
        {
            ui->dynamicLayout->removeWidget(lastSetWidget);
            lastSetWidget->hide();
        }

        if (m_simModel)
        {
            delete m_simModel;
        }

        if (m_simView)
        {
            delete m_simView;
        }

        switch (arg)
        {
        case 7:
        {
            m_simModel = new simulationModel7(); /* Create simulation model */
            m_simView = new simulationView7(); /* Create simulation view */
            m_simView->setSimulationModel(m_simModel); /* Set simulation model */
            m_simView->updateView(); /* Update view values according model */
        }
            break;
        case 8:
        {
            m_simModel = new simulationModel8(); /* Create simulation model */
            m_simView = new simulationView8(); /* Create simulation view */
            m_simView->setSimulationModel(m_simModel); /* Set simulation model */
            m_simView->updateView(); /* Update view values according model */
        }
            break;
        default:
        {
            m_simModel = new baseSimulationModel(); /* Create simulation model */
            m_simView = new baseSimulationView(); /* Create simulation view */
        }
        }

        lastSetWidget = m_simView;
        ui->dynamicLayout->addWidget(lastSetWidget);
        lastSetWidget->show();

        /* Update common settings */
        ui->duration->setValue(m_simModel->duration());
        ui->stepTime->setValue(m_simModel->simulationTime());
        ui->controlTime->setValue(m_simModel->controlTime());
    }
}
