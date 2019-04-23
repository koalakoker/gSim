#ifndef STDPID_H
#define STDPID_H

#include "simmodules_global.h"

#include "stransfer.h"

class SIMMODULESSHARED_EXPORT STDPID : public STransfer
{
public:
    STDPID(double kp, double ki, double kd, double dt, double sat);

    SDataVector execute(SDataVector in);

private:
    double m_kp;
    double m_ki;
    double m_kd;
    double m_dt;
    double m_sat;
    double m_intTerm;
    double m_prev_err;
};

#endif // STDPID_H
