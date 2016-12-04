#ifndef SIMULATIONMODEL6_H
#define SIMULATIONMODEL6_H

#include "baseSimulationModel.h"

class simulationModel6 : public baseSimulationModel
{
public:
    simulationModel6();

    /* Specific params for simulation 7 */
    double m_pi_kp;
    double m_pi_ki;
    double m_pi_kd;
    double m_pi_n;

    double m_r;
    double m_l;

    void startSimulation(void);
};

#endif // SIMULATIONMODEL6_H
