#include "simulationView8.h"
#include "ui_simulationView8.h"
#include "simulationModel8.h"

simulationView8::simulationView8() :
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
}
