#include "specificsimparamsempty.h"
#include "ui_specificsimparamsempty.h"

SpecificSimParamsEmpty::SpecificSimParamsEmpty(QWidget *parent) :
    QWidget(parent)
{
}

SpecificSimParamsEmpty::~SpecificSimParamsEmpty()
{
    delete ui;
}

void SpecificSimParamsEmpty::setSimulationModel(mainSimulation* sim)
{
    m_sim = sim;
}

void SpecificSimParamsEmpty::updateView(void)
{
}

void SpecificSimParamsEmpty::updateModel(void)
{
}
