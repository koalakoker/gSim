#ifndef STPID_H
#define STPID_H

#include "simulation/stransfer.h"
#include "simulation/stfdiscretefirstorder.h"

class STPID : public STransfer
{
public:
    typedef enum
    {
        ForwardEuler,
        BackwardEuler,
        Trapezoidal
    } TransformType_t;

    STPID(double kp, double ki, double kd, double n, double ts, TransformType_t transform = BackwardEuler);

    SDataVector execute(SDataVector in);

private:
    double m_kp;
    double m_ki;
    double m_kd;
    double m_ts;
    double m_n;

    STFDiscreteFirstOrder m_intTF;
    STFDiscreteFirstOrder m_derTF;
};

#endif // STPID_H
