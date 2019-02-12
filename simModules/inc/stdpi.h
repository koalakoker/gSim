#ifndef STDPI_H
#define STDPI_H

#include "simmodules_global.h"

#include "stransfer.h"

class SIMMODULESSHARED_EXPORT STDPI : public STransfer
{
public:
    STDPI(double kp, double ki, double dt, double sat);

    SDataVector execute(SDataVector in);

private:
    double m_dt;

    double m_kp;
    double m_ki;

    double m_sat;
    double m_intTerm;
};

#endif // STDPI_H
