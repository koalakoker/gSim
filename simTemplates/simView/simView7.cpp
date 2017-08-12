#include "simView7.h"
#include "ui_simView7.h"
#include "simTemplates/simModel/simModel7.h"

simView7::simView7(QWidget *parent) :
    baseSimView(parent),
    ui(new Ui::simView7)
{
    ui->setupUi(this);
}

simView7::~simView7()
{
    delete ui;
}

void simView7::updateView(void)
{
    simModel7* sim = (simModel7*) m_simModel;
    ui->kp->setValue(sim->m_pi_kp);
    ui->ki->setValue(sim->m_pi_ki);
    ui->kd->setValue(sim->m_pi_kd);
    ui->n->setValue(sim->m_pi_n);
    ui->r->setValue(sim->m_r);
    ui->l->setValue(sim->m_l);
}

void simView7::updateModel(void)
{
    simModel7* sim = (simModel7*) m_simModel;
    sim->m_pi_kp = ui->kp->value();
    sim->m_pi_ki = ui->ki->value();
    sim->m_pi_kd = ui->kd->value();
    sim->m_pi_n = ui->n->value();
    sim->m_r = ui->r->value();
    sim->m_l = ui->l->value();
}
