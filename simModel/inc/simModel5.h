#ifndef SIMMODEL5_H
#define SIMMODEL5_H

#include "baseSimModel.h"

class simModel5 : public baseSimModel
{
public:
    simModel5();

    /* Specific params for sim 7 */
    double m_pi_kp;
    double m_pi_ki;
    double m_pi_kd;
    double m_pi_n;

    double m_r;
    double m_l;

    void startSim(void);
};

#endif // SIMMODEL5_H
