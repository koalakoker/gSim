#include "simulationView7.h"
#include "ui_simulationView7.h"
#include "simulationmodel7.h"

simulationView7::simulationView7(QWidget *parent) :
    baseSimulationView(parent),
    ui(new Ui::simulationView7)
{
    ui->setupUi(this);
}

simulationView7::~simulationView7()
{
    delete ui;
}

void simulationView7::updateView(void)
{
    simulationModel7* sim = (simulationModel7*) m_sim;
    ui->kp->setValue(sim->m_pi_kp);
    ui->ki->setValue(sim->m_pi_ki);
    ui->kd->setValue(sim->m_pi_kd);
    ui->n->setValue(sim->m_pi_n);
    ui->r->setValue(sim->m_r);
    ui->l->setValue(sim->m_l);
}

void simulationView7::updateModel(void)
{
    simulationModel7* sim = (simulationModel7*) m_sim;
    sim->m_pi_kp = ui->kp->value();
    sim->m_pi_ki = ui->ki->value();
    sim->m_pi_kd = ui->kd->value();
    sim->m_pi_n = ui->n->value();
    sim->m_r = ui->r->value();
    sim->m_l = ui->l->value();
}
