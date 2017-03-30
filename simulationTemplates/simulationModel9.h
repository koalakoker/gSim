#ifndef SIMULATIONMODEL9_H
#define SIMULATIONMODEL9_H

#include "baseSimulationModel.h"

class simulationModel9 : public baseSimulationModel
{
public:
    simulationModel9();

    /* Specific params for simulation 9 */

    /* Motor params */
    double m_torque;
    double m_polesPairs;
    double m_inertia;
    double m_friction;

    double m_acceleration;
    double m_cruiseSpeed;
    double m_angleStep;
    double m_movementDuration;

    double m_t1;
    double m_t2;
    double m_teta0;
    double m_teta1;
    double m_teta2;

    double m_omega;
    double m_teta;

    /* Plots */
    bool m_anglePlot;

    void startSimulation(void);

    // PI
    double PI_KP;
    double PI_KI;

};

#endif // SIMULATIONMODEL9_H
