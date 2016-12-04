#ifndef SIMULATIONMODEL3_H
#define SIMULATIONMODEL3_H

#include "baseSimulationModel.h"

class simulationModel3 : public baseSimulationModel
{
public:
    simulationModel3();

    /* Specific params for simulation 3 */
    double m_pi_kp;
    double m_pi_ki;
    double m_pi_kd;
    double m_pi_n;

    double m_r;
    double m_l;

    void startSimulation(void);
};

#endif // SIMULATIONMODEL3_H
