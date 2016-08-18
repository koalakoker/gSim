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
    sim.startSimulation();
}
