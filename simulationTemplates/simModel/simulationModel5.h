#ifndef SIMULATIONMODEL5_H
#define SIMULATIONMODEL5_H

#include "baseSimulationModel.h"

class simulationModel5 : public baseSimulationModel
{
public:
    simulationModel5();

    /* Specific params for simulation 7 */
    double m_pi_kp;
    double m_pi_ki;
    double m_pi_kd;
    double m_pi_n;

    double m_r;
    double m_l;

    void startSimulation(void);
};

#endif // SIMULATIONMODEL5_H
