#include "gsim.h"
#include "ui_gsim.h"

gSim::gSim(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::gSim)
{
    ui->setupUi(this);

    ui->duration->setValue(sim.duration());
    ui->stepTime->setValue(sim.simulationTime());
    ui->controlTime->setValue(sim.controlTime());

    ui->kp->setValue(sim.m_pi_kp);
    ui->ki->setValue(sim.m_pi_ki);

    ui->R->setValue(sim.m_r);
    ui->L->setValue(sim.m_l);
}

gSim::~gSim()
{
    delete ui;
}

void gSim::on_startSimulation_clicked()
{
    sim.setDuration(ui->duration->value());
    sim.setSimulationTime(ui->stepTime->value());
    sim.setControlTime(ui->controlTime->value());
    sim.m_pi_kp = ui->kp->value();
    sim.m_pi_ki = ui->ki->value();
    sim.m_r = ui->R->value();
    sim.m_l = ui->L->value();
    sim.startSimulation();
}
