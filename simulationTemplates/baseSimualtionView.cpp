#include "baseSimulationView.h"
#include "ui_baseSimulationView.h"

baseSimulationView::baseSimulationView(QWidget *parent) :
    QWidget(parent)
{
}

baseSimulationView::~baseSimulationView()
{
    delete ui;
}

void baseSimulationView::setSimulationModel(baseSimulationModel* sim)
{
    m_sim = sim;
}

void baseSimulationView::updateView(void)
{
}

void baseSimulationView::updateModel(void)
{
}
