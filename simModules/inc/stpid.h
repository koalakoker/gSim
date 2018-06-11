#ifndef STPID_H
#define STPID_H

#include "simmodules_global.h"

#include "stransfer.h"
#include "stfintegrator.h"
#include "stfderivatorfitered.h"

class SIMMODULESSHARED_EXPORT STPID : public STransfer
{
public:
    STPID(double kp, double ki, double kd, double n, double ts, DiscreteTimeTransformType_t transform = BackwardEuler);

    SDataVector execute(SDataVector in);

public:
    double m_kp;
    double m_ki;
    double m_kd;

    double m_maxOut;
    double m_maxIntTerm;

    STFIntegrator m_intTF;
    STFDerivatorFitered m_derTF;
};

#endif // STPID_H
