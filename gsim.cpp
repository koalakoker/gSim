#include <QTime>
#include "gsim.h"
#include "ui_gsim.h"

gSim::gSim(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::gSim)
{
    // Create all possible specific parameters to be shown in the Dyamic Layout
    sspEmpty = new SpecificSimParamsEmpty();

    sspT8 = new SpecificSimParamsTest8();
    sspT8->setMotSpeedRads(m_sim.m_t8_motSpeedRads);
    sspT8->setExcFreq(m_sim.m_t8_exc_freq);
    sspT8->setExcAmpl(m_sim.m_t8_exc_ampl);
    sspT8->setSinAttenuation(m_sim.m_t8_sin_att);
    sspT8->setSinDelay(m_sim.m_t8_sin_delay);
    sspT8->setSinOffset(m_sim.m_t8_sin_offset);
    sspT8->setCosAttenuation(m_sim.m_t8_cos_att);
    sspT8->setCosDelay(m_sim.m_t8_cos_delay);
    sspT8->setCosOffset(m_sim.m_t8_cos_offset);

    lastSetWidget = NULL;

    ui->setupUi(this);

    ui->duration->setValue(m_sim.duration());
    ui->stepTime->setValue(m_sim.simulationTime());
    ui->controlTime->setValue(m_sim.controlTime());
    ui->simulation->setValue(m_sim.m_simulation);

    connect(&m_sim, SIGNAL(updateProgress(double)), this, SLOT(updateProgress(double)));
}

gSim::~gSim()
{
    delete ui;
}

void gSim::on_startSimulation_clicked()
{
    QTime t;
    t.start();

    m_sim.setDuration(ui->duration->value());
    m_sim.setSimulationTime(ui->stepTime->value());
    m_sim.setControlTime(ui->controlTime->value());

    // Update specific params for Test 8
    m_sim.m_t8_motSpeedRads = sspT8->getMotSpeedRads();
    m_sim.m_t8_exc_freq = sspT8->getExcFreq();
    m_sim.m_t8_exc_ampl = sspT8->getExcAmpl();
    m_sim.m_t8_sin_att = sspT8->getSinAttenuation();
    m_sim.m_t8_sin_delay = sspT8->getSinDelay();
    m_sim.m_t8_sin_offset = sspT8->getSinOffset();
    m_sim.m_t8_cos_att = sspT8->getCosAttenuation();
    m_sim.m_t8_cos_delay = sspT8->getCosDelay();
    m_sim.m_t8_cos_offset = sspT8->getCosOffset();

    m_sim.m_simulation = ui->simulation->value();
    m_sim.startSimulation();

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
