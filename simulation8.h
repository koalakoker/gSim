#ifndef SIMULATION8_H
#define SIMULATION8_H

#include "mainsimulation.h"


class simulation8 : public mainSimulation
{
public:
    simulation8();

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

#endif // SIMULATION8_H
