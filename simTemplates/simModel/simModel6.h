#ifndef SIMMODEL6_H
#define SIMMODEL6_H

#include "baseSimModel.h"

class simModel6 : public baseSimModel
{
public:
    simModel6();

    /* Specific params for sim 7 */
    double m_pi_kp;
    double m_pi_ki;
    double m_pi_kd;
    double m_pi_n;

    double m_r;
    double m_l;

    void startSim(void);
};

#endif // SIMMODEL6_H
