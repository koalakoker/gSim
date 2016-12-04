#include "baseSimulationModel.h"

baseSimulationModel::baseSimulationModel()
{
    /* Set simulation number */
    m_simulation = 0;

    /* Default common params */
    m_t = 0;
    m_ts = 0.00005;
    m_tc = 0.00005;
    m_duration = 0.02;
}

void baseSimulationModel::startSimulation(void) {}
