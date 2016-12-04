#include <QTime>
#include "gsim.h"
#include "ui_gsim.h"
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

#define DEFAULT_SIMULATION 0

gSim::gSim(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::gSim)
{
    m_simModel = NULL;
    m_simView = NULL;

    ui->setupUi(this);

    setSimulation(DEFAULT_SIMULATION); /* To be called after UI setup */

    // Test
    connect(&testTim, SIGNAL(timeout()), this, SLOT(testTimeout()));
    testTim.start(SIM_TEST);
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

    if (m_simView)
    {
        // Update specific params
        m_simView->updateModel(); /* Update model before to start simulation */
    }

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
        if (m_simModel)
        {
            delete m_simModel;
            m_simModel = NULL;
        }

        if (m_simView)
        {
            delete m_simView;
            m_simView = NULL;
        }

        switch (arg)
        {
        case 0:
        {
            m_simModel = new simulationModel0(); /* Create simulation model */
        }
            break;
        case 1:
        {
            m_simModel = new simulationModel1(); /* Create simulation model */
        }
            break;
        case 2:
        {
            m_simModel = new simulationModel2(); /* Create simulation model */
        }
            break;
        case 3:
        {
            m_simModel = new simulationModel3(); /* Create simulation model */
        }
            break;
        case 4:
        {
            m_simModel = new simulationModel4(); /* Create simulation model */
        }
            break;
        case 5:
        {
            m_simModel = new simulationModel5(); /* Create simulation model */
            m_simView = new simulationView7(); /* Create simulation view */
            m_simView->setSimulationModel(m_simModel); /* Set simulation model */
            m_simView->updateView(); /* Update view values according model */
        }
            break;
        case 6:
        {
            m_simModel = new simulationModel6(); /* Create simulation model */
            m_simView = new simulationView7(); /* Create simulation view */
            m_simView->setSimulationModel(m_simModel); /* Set simulation model */
            m_simView->updateView(); /* Update view values according model */
        }
            break;
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

        if (m_simView)
        {
            ui->dynamicLayout->addWidget(m_simView);
            m_simView->show();
        }

        /* Update common settings */
        ui->duration->setValue(m_simModel->duration());
        ui->stepTime->setValue(m_simModel->simulationTime());
        ui->controlTime->setValue(m_simModel->controlTime());

        connect(m_simModel, SIGNAL(updateProgress(double)), this, SLOT(updateProgress(double)));
    }
}

void gSim::testTimeout(void)
{
    testTim.start(SIM_TEST);
    int last = qrand()%12;
    ui->simulation->setValue(last);
}
