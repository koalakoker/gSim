#ifndef STPMSMDQ_H
#define STPMSMDQ_H

#include "simmodules_global.h"

#include "smotor.h"
#include "stfintegrator.h"
#include "pmsmvars.h"

class SIMMODULESSHARED_EXPORT STPMSMdq : public SMotor
{
public:
    STPMSMdq(double rs, double ld, double lq, double polesPairs, double magnetFlux, double inertia,
             double fbrk, double wbbrk, double fc, double f,
             double ts,
             double brakeTorque = 0.0, double coggingTorqueModule = 0.0, double coggingTorqueAngleDisplacement = 0.0,
             DiscreteTimeTransformType_t transform = BackwardEuler);

    void execute(SDataVector in); // in have single inputs (slot) with two value vd [0,0] and vq [0,1]

    PMSMVars& vars() {return m_vars;}

private:
    double m_rs;
    double m_ld;
    double m_lq;
    double m_polesPairs;
    double m_magneticFlux;
    double m_inertia;

    double m_fbrk;
    double m_wbrk;
    double m_fc;
    double m_f;

    double m_brakeTorque;
    double m_coggingTorqueModule;
    double m_coggingTorqueAngleDisplacement;

    // Vars
    PMSMVars m_vars;

    // Integrators
    STFIntegrator m_idIntTF;
    STFIntegrator m_iqIntTF;
    STFIntegrator m_wIntTF;
    STFIntegrator m_thIntTF;
};

#endif // STPMSMDQ_H
