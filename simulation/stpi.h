#ifndef STPI_H
#define STPI_H

#include "simulation/stransfer.h"

class STPI : public STransfer
{
public:
    STPI(double kp, double ki, double ts);

    SDataVector execute(SDataVector in);

private:
    double m_kp;
    double m_ki;
    double m_ts;

    double m_a;
    double m_b;

    double m_ePrev;
    double m_uPrev;
};

#endif // STPI_H
