#ifndef SIMULATIONMODEL9_H
#define SIMULATIONMODEL9_H

#include "baseSimulationModel.h"

class simulationModel9 : public baseSimulationModel
{
public:
    simulationModel9();

    /* Specific params for simulation 9 */
    double m_exc_freq;
    double m_exc_ampl;
    double m_sin_att;
    double m_sin_delay;
    double m_sin_offset;
    double m_cos_att;
    double m_cos_delay;
    double m_cos_offset;

    /* Demodulated signals sin/cos */
    double m_resSinDem;
    double m_resCosDem;
    int k; /* Sampling point selection k = 0,1, ...*/

    /* Motor params */
    double m_torque;
    double m_polesPairs;
    double m_inertia;
    double m_friction;

    /* Plots */
    bool m_excitingPlot;
    bool m_outputsPlot;
    bool m_demuxOutputsPlot;
    bool m_thetaPlot;
    bool m_omegaPlot;
    bool m_deltaAngle;

    void startSimulation(void);

    // Resolver simulation
    void resolverInit(void);
    void resolverExec(void);
    double phi; // Tracked angle
    double omega; // Tracked speed
    // PI
    double PI_KP;
    double PI_KI;

};

#endif // SIMULATIONMODEL9_H
