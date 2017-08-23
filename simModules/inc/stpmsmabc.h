#ifndef STPMSMABC_H
#define STPMSMABC_H

#include "simmodules_global.h"

#include "smotor.h"
#include "stpmsmdq.h"
#include "stabctodq.h"
#include "stdqtoabc.h"
#include "pmsmvars.h"

class SIMMODULESSHARED_EXPORT STPMSMabc : public SMotor
{
public:
    STPMSMabc(double rs, double ld, double lq, double polesPairs, double magnetFlux, double inertia, double friction, double ts,
              double brakeTorque = 0,
              DiscreteTimeTransformType_t transform = BackwardEuler);

    void execute(SDataVector in); // in have single inputs (slot) with three value va [0,0], vb [0,1] and vb [0,2]

    PMSMVars& vars() {return m_vars;}

private:
    STPMSMdq m_PMSMdq;
    PMSMVars m_vars;

    STabctodq m_abctodq;
    STdqtoabc m_dqtoabc;
};

#endif // STPMSMABC_H
