#include <QTime>
#include "gsim.h"
#include "ui_gsim.h"

gSim::gSim(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::gSim)
{
    m_simModel = NULL;
    m_simView = NULL;

    ui->setupUi(this);

    setSimulation(); /* To be called after UI setup */
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

void gSim::setSimulation(void)
{
    m_simModel = &m_simModel0;

    /* Update common settings */
    ui->duration->setValue(m_simModel->duration());
    ui->stepTime->setValue(m_simModel->simulationTime());
    ui->controlTime->setValue(m_simModel->controlTime());

    connect(m_simModel, SIGNAL(updateProgress(double)), this, SLOT(updateProgress(double)));
}
