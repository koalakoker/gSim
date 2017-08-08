#ifndef SIMMODEL3_H
#define SIMMODEL3_H

#include "baseSimModel.h"

class simModel3 : public baseSimModel
{
public:
    simModel3();

    /* Specific params for sim 3 */
    double m_pi_kp;
    double m_pi_ki;
    double m_pi_kd;
    double m_pi_n;

    double m_r;
    double m_l;

    void startSim(void);
};

#endif // SIMMODEL3_H
