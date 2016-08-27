#ifndef STPMSMQD_H
#define STPMSMQD_H

#include "simulation/stransfer.h"
#include "simulation/stfintegrator.h"

class STPMSMqd : public STransfer
{
public:
    STPMSMqd(double rs, double ld, double lq, double polesPairs, double magnetFlux, double inertia, double friction, double ts,
             double brakeTorque = 0,
             DiscreteTimeTransformType_t transform = BackwardEuler);

    SDataVector execute(SDataVector in); // in have single inputs (slot) with two value vd [0,0] and vq [0,1]

private:
    double m_rs;
    double m_ld;
    double m_lq;
    double m_polesPairs;
    double m_magneticFlux;
    double m_inertia;
    double m_friction;
    double m_brakeTorque;

    // State variables
    double m_idPrev;
    double m_iqPrev;
    double m_wPrev;

    // Integrators
    STFIntegrator m_idIntTF;
    STFIntegrator m_iqIntTF;
    STFIntegrator m_wIntTF;
    STFIntegrator m_thIntTF;
};

class PMSMVars : public SDataVector
{
public:
    PMSMVars();
    PMSMVars(SDataVector dv);

    SDataVector toDataVector();

    double Iq;
    double Id;
    double T;
    double Wm;
    double Th;
};

#endif // STPMSMQD_H
