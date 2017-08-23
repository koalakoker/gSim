#ifndef SMOTORMECH_H
#define SMOTORMECH_H

#include "simmodules_global.h"

#include "smotor.h"
#include "stfintegrator.h"
#include "motormechvars.h"

class SIMMODULESSHARED_EXPORT SMotorMech : public SMotor
{
public:
    SMotorMech(double polesPairs, double inertia, double friction, double ts,
             double brakeTorque = 0,
             DiscreteTimeTransformType_t transform = BackwardEuler);

    void execute(SDataVector in); // in have single inputs (slot) with two value vd [0,0] and vq [0,1]

    MotorMechVars& vars() {return m_vars;}

private:
    double m_polesPairs;
    double m_inertia;
    double m_friction;
    double m_brakeTorque;

    // Vars
    MotorMechVars m_vars;

    // Integrators
    STFIntegrator m_wIntTF;
    STFIntegrator m_thIntTF;
};

#endif // SMOTORMECH_H
