#ifndef SIMMODEL8_H
#define SIMMODEL8_H

#include "baseSimModel.h"

class simModel8 : public baseSimModel
{
public:
    simModel8();

    /* Specific params for sim 8 */
    double m_motSpeedRads;
    double m_exc_freq;
    double m_exc_ampl;
    double m_sin_att;
    double m_sin_delay;
    double m_sin_offset;
    double m_cos_att;
    double m_cos_delay;
    double m_cos_offset;

    /* Plots */
    bool excitingPlot;
    bool outputsPlot;
    bool thetaPlot;

    void startSim(void);
};

#endif // SIMMODEL8_H
