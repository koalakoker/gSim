#include "gsim.h"
#include "ui_gsim.h"

gSim::gSim(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::gSim)
{
    ui->setupUi(this);

    ui->duration->setValue(sim.duration());
    ui->stepTime->setValue(sim.stepTime());
}

gSim::~gSim()
{
    delete ui;
}

void gSim::on_startSimulation_clicked()
{
    sim.setDuration(ui->duration->value());
    sim.setStepTime(ui->stepTime->value());
    sim.startSimulation();
}
