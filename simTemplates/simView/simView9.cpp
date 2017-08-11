#include "simView9.h"
#include "ui_simView9.h"
#include "simTemplates/simModel/simModel9.h"

simView9::simView9(QWidget *parent) :
    baseSimView(parent),
    ui(new Ui::SpecificSimParamsTest9)
{
    ui->setupUi(this);
}

simView9::~simView9()
{
    delete ui;
}

void simView9::updateView(void)
{
    simModel9* sim = (simModel9*) m_sim;
    ui->j->setValue(sim->m_j);
    ui->f->setValue(sim->m_f);
    ui->pp->setValue(sim->m_pp);
    ui->kp->setValue(sim->m_pi_kp);
    ui->ki->setValue(sim->m_pi_ki);
    ui->w_tetaPlot->setChecked(sim->m_wTetaPlot);
}

void simView9::updateModel(void)
{
    simModel9* sim = (simModel9*) m_sim;
    sim->m_j = ui->j->value();
    sim->m_f = ui->f->value();
    sim->m_pp = ui->pp->value();
    sim->m_pi_kp = ui->kp->value();
    sim->m_pi_ki = ui->ki->value();
    sim->m_wTetaPlot = ui->w_tetaPlot->isChecked();
}
