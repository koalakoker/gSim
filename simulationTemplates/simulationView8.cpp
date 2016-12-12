#include "simulationView8.h"
#include "ui_simulationView8.h"
#include "simulationModel8.h"

simulationView8::simulationView8(QWidget *parent) :
    baseSimulationView(parent),
    ui(new Ui::SpecificSimParamsTest8)
{
    ui->setupUi(this);
}

simulationView8::~simulationView8()
{
    delete ui;
}

void simulationView8::updateView(void)
{
    simulationModel8* sim = (simulationModel8*) m_sim;
    ui->motSpeedRads->setValue(sim->m_motSpeedRads);
    ui->excFreq->setValue(sim->m_exc_freq);
    ui->excAmp->setValue(sim->m_exc_ampl);
    ui->sinAttenuation->setValue(sim->m_sin_att);
    ui->sinDelay->setValue(sim->m_sin_delay);
    ui->sinOffset->setValue(sim->m_sin_offset);
    ui->cosAttenuation->setValue(sim->m_cos_att);
    ui->cosDelay->setValue(sim->m_cos_delay);
    ui->cosOffset->setValue(sim->m_cos_offset);
    ui->excitingPlot->setChecked(sim->excitingPlot);
    ui->outputPlot->setChecked(sim->outputsPlot);
    ui->thetaPlot->setChecked(sim->thetaPlot);

    ui->PI_KP->setValue(sim->PI_KP);
    ui->PI_KI->setValue(sim->PI_KI);
    ui->LP_Beta->setValue(sim->LPF_Beta);
}

void simulationView8::updateModel(void)
{
    simulationModel8* sim = (simulationModel8*) m_sim;
    sim->m_motSpeedRads = ui->motSpeedRads->value();
    sim->m_exc_freq = ui->excFreq->value();
    sim->m_exc_ampl = ui->excAmp->value();
    sim->m_sin_att = ui->sinAttenuation->value();
    sim->m_sin_delay = ui->sinDelay->value();
    sim->m_sin_offset = ui->sinOffset->value();
    sim->m_cos_att = ui->cosAttenuation->value();
    sim->m_cos_delay = ui->cosDelay->value();
    sim->m_cos_offset = ui->cosOffset->value();
    sim->excitingPlot = ui->excitingPlot->isChecked();
    sim->outputsPlot = ui->outputPlot->isChecked();
    sim->thetaPlot = ui->thetaPlot->isChecked();

    sim->PI_KP = ui->PI_KP->value();
    sim->PI_KI = ui->PI_KI->value();
    sim->LPF_Beta = ui->LP_Beta->value();
}
