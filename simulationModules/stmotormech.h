#ifndef STMOTORMECH_H
#define STMOTORMECH_H

#include "simulationModules/smotor.h"
#include "simulationModules/stfintegrator.h"
#include "simulationModules/motormechvars.h"

class STMotorMech : public SMotor
{
public:
    STMotorMech(double polesPairs, double inertia, double friction, double ts,
             bool normalizeAngle = true,
             double brakeTorque = 0,
             DiscreteTimeTransformType_t transform = BackwardEuler);

    void execute(SDataVector in); // in have single inputs (slot) with two value vd [0,0] and vq [0,1]

    MotorMechVars& vars() {return m_vars;}

private:
    double m_polesPairs;
    double m_inertia;
    double m_friction;
    double m_brakeTorque;
    bool m_normalizeAngle;

    // Vars
    MotorMechVars m_vars;

    // Integrators
    STFIntegrator m_wIntTF;
    STFIntegrator m_thIntTF;
};

#endif // STMOTORMECH_H
