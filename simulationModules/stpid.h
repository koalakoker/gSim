#ifndef STPID_H
#define STPID_H

#include "simulationModules/stransfer.h"
#include "simulationModules/stfintegrator.h"
#include "simulationModules/stfderivatorfitered.h"

class STPID : public STransfer
{
public:
    STPID(double kp, double ki, double kd, double n, double ts, DiscreteTimeTransformType_t transform = BackwardEuler);

    SDataVector execute(SDataVector in);

private:
    double m_kp;
    double m_ki;
    double m_kd;
    //double m_ts;
    //double m_n;

    STFIntegrator m_intTF;
    STFDerivatorFitered m_derTF;
};

#endif // STPID_H
