#ifndef SIMULATIONMODEL8_H
#define SIMULATIONMODEL8_H

#include "baseSimulationModel.h"


class simulationModel8 : public baseSimulationModel
{
public:
    simulationModel8();

    /* Specific params for simulation 8 */
    double m_motSpeedRads;
    double m_exc_freq;
    double m_exc_ampl;
    double m_sin_att;
    double m_sin_delay;
    double m_sin_offset;
    double m_cos_att;
    double m_cos_delay;
    double m_cos_offset;

    void startSimulation(void);
};

#endif // SIMULATIONMODEL8_H
