#ifndef SIMMODEL4_H
#define SIMMODEL4_H

#include "baseSimModel.h"

class simModel4 : public baseSimModel
{
public:
    simModel4();

    /* Specific params for sim 4 */
    double m_pi_kp;
    double m_pi_ki;
    double m_pi_kd;
    double m_pi_n;

    double m_r;
    double m_l;

    void startSim(void);
};

#endif // SIMMODEL4_H
