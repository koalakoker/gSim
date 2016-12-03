#ifndef SIMULATIONMODEL7_H
#define SIMULATIONMODEL7_H

#include "baseSimulationModel.h"

class simulationModel7 : public baseSimulationModel
{
public:
    simulationModel7();

    /* Specific params for simulation 7 */
    double m_pi_kp;
    double m_pi_ki;
    double m_pi_kd;
    double m_pi_n;

    double m_r;
    double m_l;

    void startSimulation(void);
};

#endif // SIMULATIONMODEL7_H
