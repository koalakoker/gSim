#include "simulationView9.h"
#include "ui_simulationView9.h"
#include "simulationModel9.h"

simulationView9::simulationView9(QWidget *parent) :
    baseSimulationView(parent),
    ui(new Ui::SpecificSimParamsTest9)
{
    ui->setupUi(this);
}

simulationView9::~simulationView9()
{
    delete ui;
}

void simulationView9::updateView(void)
{
    simulationModel9* sim = (simulationModel9*) m_sim;
    ui->excFreq->setValue(sim->m_exc_freq);
    ui->excAmp->setValue(sim->m_exc_ampl);
    ui->sinAttenuation->setValue(sim->m_sin_att);
    ui->sinDelay->setValue(sim->m_sin_delay);
    ui->sinOffset->setValue(sim->m_sin_offset);
    ui->cosAttenuation->setValue(sim->m_cos_att);
    ui->cosDelay->setValue(sim->m_cos_delay);
    ui->cosOffset->setValue(sim->m_cos_offset);

    ui->inertia->setValue(sim->m_inertia);
    ui->friction->setValue(sim->m_friction);

    ui->excitingPlot->setChecked(sim->m_excitingPlot);
    ui->outputPlot->setChecked(sim->m_outputsPlot);
    ui->outputDemuxPlot->setChecked(sim->m_demuxOutputsPlot);
    ui->thetaPlot->setChecked(sim->m_thetaPlot);
    ui->omegaPlot->setChecked(sim->m_omegaPlot);
    ui->deltaAngle->setChecked(sim->m_deltaAngle);

    ui->PI_KP->setValue(sim->PI_KP);
    ui->PI_KI->setValue(sim->PI_KI);
}

void simulationView9::updateModel(void)
{
    simulationModel9* sim = (simulationModel9*) m_sim;
    sim->m_exc_freq = ui->excFreq->value();
    sim->m_exc_ampl = ui->excAmp->value();
    sim->m_sin_att = ui->sinAttenuation->value();
    sim->m_sin_delay = ui->sinDelay->value();
    sim->m_sin_offset = ui->sinOffset->value();
    sim->m_cos_att = ui->cosAttenuation->value();
    sim->m_cos_delay = ui->cosDelay->value();
    sim->m_cos_offset = ui->cosOffset->value();

    sim->m_inertia = ui->inertia->value();
    sim->m_friction = ui->friction->value();

    sim->m_excitingPlot = ui->excitingPlot->isChecked();
    sim->m_outputsPlot = ui->outputPlot->isChecked();
    sim->m_demuxOutputsPlot = ui->outputDemuxPlot->isChecked();
    sim->m_thetaPlot = ui->thetaPlot->isChecked();
    sim->m_omegaPlot = ui->omegaPlot->isChecked();
    sim->m_deltaAngle = ui->deltaAngle->isChecked();

    sim->PI_KP = ui->PI_KP->value();
    sim->PI_KI = ui->PI_KI->value();
}
