#include <QTime>
#include "gsim.h"
#include "ui_gsim.h"

#define DEFAULT_SIMULATION 9

gSim::gSim(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::gSim)
{
    m_simModel = NULL;
    m_simView = NULL;
    m_lastSetWidget = NULL;

    ui->setupUi(this);

    setSimulation(DEFAULT_SIMULATION); /* To be called after UI setup */

#ifdef TEST
    connect(&testTim, SIGNAL(timeout()), this, SLOT(testTimeout()));
    testTim.start(SIM_TEST);
#endif
}

gSim::~gSim()
{
    if (m_lastSetWidget != NULL)
    {
        ui->dynamicLayout->removeWidget(m_lastSetWidget);
    }

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
        if (m_lastSetWidget != NULL)
        {
            ui->dynamicLayout->removeWidget(m_lastSetWidget);
            m_lastSetWidget->hide();
        }

        m_simView = NULL;

        switch (arg)
        {
        case 0:
        {
            m_simModel = &m_simModel0;
        }
            break;
        case 1:
        {
            m_simModel = &m_simModel1;
        }
            break;
        case 2:
        {
            m_simModel = &m_simModel2;
        }
            break;
        case 3:
        {
            m_simModel = &m_simModel3;
        }
            break;
        case 4:
        {
            m_simModel = &m_simModel4;
        }
            break;
        case 5:
        {
            m_simModel = &m_simModel5;
            m_simView = &m_simView7;
            m_simView->setSimulationModel(m_simModel); /* Set simulation model */
            m_simView->updateView(); /* Update view values according model */
        }
            break;
        case 6:
        {
            m_simModel = &m_simModel6;
            m_simView = &m_simView7;
            m_simView->setSimulationModel(m_simModel); /* Set simulation model */
            m_simView->updateView(); /* Update view values according model */
        }
            break;
        case 7:
        {
            m_simModel = &m_simModel7;
            m_simView = &m_simView7;
            m_simView->setSimulationModel(m_simModel); /* Set simulation model */
            m_simView->updateView(); /* Update view values according model */
        }
            break;
        case 8:
        {
            m_simModel = &m_simModel8;
            m_simView = &m_simView8;
            m_simView->setSimulationModel(m_simModel); /* Set simulation model */
            m_simView->updateView(); /* Update view values according model */
        }
            break;
        case 9:
        {
            m_simModel = &m_simModel9;
            m_simView = &m_simView9;
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
            m_lastSetWidget = m_simView;
            ui->dynamicLayout->addWidget(m_simView);
            m_simView->show();
        }

        /* Update common settings */
        bool oldState = ui->simulation->blockSignals(true);
        ui->simulation->setValue(m_simModel->m_simulation);
        ui->simulation->blockSignals(oldState);
        ui->description->setText(m_simModel->m_description);
        ui->duration->setValue(m_simModel->duration());
        ui->stepTime->setValue(m_simModel->simulationTime());
        ui->controlTime->setValue(m_simModel->controlTime());

        connect(m_simModel, SIGNAL(updateProgress(double)), this, SLOT(updateProgress(double)));
    }
}

void gSim::testTimeout(void)
{
    testTim.start(SIM_TEST);
    int last = qrand() % MAX_TEST_NUM;
    ui->simulation->setValue(last);
}
