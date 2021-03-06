#include "simulationView9.h"
#include "ui_simulationView9.h"
#include "simulationModel9.h"

simulationView9::simulationView9(QWidget *parent) :
    baseSimulationView(parent),
    ui(new Ui::SpecificSimParamsTest9)
{
    ui->setupUi(this);
}

simulationView9::~simulationView9()
{
    delete ui;
}

void simulationView9::updateView(void)
{
    simulationModel9* sim = (simulationModel9*) m_sim;

    ui->inertia->setValue(sim->m_inertia);
    ui->friction->setValue(sim->m_friction);

    ui->anglePlot->setChecked(sim->m_anglePlot);

    ui->PI_KP->setValue(sim->PI_KP);
    ui->PI_KI->setValue(sim->PI_KI);

    ui->jerk->setValue(sim->m_jerk);
    ui->cruiseSpeed->setValue(sim->m_cruiseSpeed);
    ui->duration->setValue(sim->m_movementDuration);
    ui->angleStep->setValue(sim->m_angleStep);
    ui->t1->setValue(sim->m_t1);
    ui->acceleration->setValue(sim->m_acceleration);
    ui->t2->setValue(sim->m_t2);
}

void simulationView9::updateModel(void)
{
    simulationModel9* sim = (simulationModel9*) m_sim;

    sim->m_inertia = ui->inertia->value();
    sim->m_friction = ui->friction->value();

    sim->m_anglePlot = ui->anglePlot->isChecked();

    sim->PI_KP = ui->PI_KP->value();
    sim->PI_KI = ui->PI_KI->value();

    sim->m_jerk = ui->jerk->value();
    sim->m_cruiseSpeed = ui->cruiseSpeed->value();
    sim->m_movementDuration = ui->duration->value();
    sim->m_angleStep = ui->angleStep->value();
}
