#include "specificsimparamsTest8.h"
#include "ui_specificsimparamsTest8.h"
#include "simulation8.h"

SpecificSimParamsTest8::SpecificSimParamsTest8() :
    ui(new Ui::SpecificSimParamsTest8)
{
    ui->setupUi(this);
}

SpecificSimParamsTest8::~SpecificSimParamsTest8()
{
    delete ui;
}

void SpecificSimParamsTest8::updateView(void)
{
    simulation8* sim = (simulation8*) m_sim;
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

void SpecificSimParamsTest8::updateModel(void)
{
    simulation8* sim = (simulation8*) m_sim;
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
