#ifndef SIMULATIONMODEL4_H
#define SIMULATIONMODEL4_H

#include "baseSimulationModel.h"

class simulationModel4 : public baseSimulationModel
{
public:
    simulationModel4();

    /* Specific params for simulation 4 */
    double m_pi_kp;
    double m_pi_ki;
    double m_pi_kd;
    double m_pi_n;

    double m_r;
    double m_l;

    void startSimulation(void);
};

#endif // SIMULATIONMODEL4_H
