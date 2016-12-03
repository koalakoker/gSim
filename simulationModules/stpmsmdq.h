#ifndef STPMSMDQ_H
#define STPMSMDQ_H

#include "simulationModules/smotor.h"
#include "simulationModules/stfintegrator.h"
#include "simulationModules/pmsmvars.h"

class STPMSMdq : public SMotor
{
public:
    STPMSMdq(double rs, double ld, double lq, double polesPairs, double magnetFlux, double inertia, double friction, double ts,
             double brakeTorque = 0,
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
    double m_friction;
    double m_brakeTorque;

    // Vars
    PMSMVars m_vars;

    // Integrators
    STFIntegrator m_idIntTF;
    STFIntegrator m_iqIntTF;
    STFIntegrator m_wIntTF;
    STFIntegrator m_thIntTF;
};

#endif // STPMSMDQ_H
