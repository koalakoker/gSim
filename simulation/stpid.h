#ifndef STPID_H
#define STPID_H

#include "simulation/stransfer.h"

class STPID : public STransfer
{
public:
    typedef enum
    {
        BackwardEuler,
    } TransformType_t;

    STPID(double kp, double ki, double kd, double n, double ts, TransformType_t transform = BackwardEuler);

    SDataVector execute(SDataVector in);

private:
    double m_kp;
    double m_ki;
    double m_kd;
    double m_ts;
    double m_n;

    double m_a0;
    double m_a1;
    double m_a2;
    double m_b1;
    double m_b2;

    double m_ePrev;
    double m_e2Prev;
    double m_uPrev;
    double m_u2Prev;
};

#endif // STPID_H
