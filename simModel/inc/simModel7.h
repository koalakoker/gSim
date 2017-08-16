#ifndef SIMMODEL7_H
#define SIMMODEL7_H

#include "baseSimModel.h"

class simModel7 : public baseSimModel
{
public:
    simModel7();

    /* Specific params for sim 7 */
    double m_pi_kp;
    double m_pi_ki;
    double m_pi_kd;
    double m_pi_n;

    double m_r;
    double m_l;

    void startSim(void);
};

#endif // SIMMODEL7_H
