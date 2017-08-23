#include "simView8.h"
#include "ui_simView8.h"
#include "simTemplates/simModel/simModel8.h"

simView8::simView8(QWidget *parent) :
    baseSimView(parent),
    ui(new Ui::SpecificSimParamsTest8)
{
    ui->setupUi(this);
}

simView8::~simView8()
{
    delete ui;
}

void simView8::updateView(void)
{
    simModel8* sim = (simModel8*) m_simModel;
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
}

void simView8::updateModel(void)
{
    simModel8* sim = (simModel8*) m_simModel;
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
}
