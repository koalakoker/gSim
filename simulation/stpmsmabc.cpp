#include "stpmsmabc.h"

STPMSMabc::STPMSMabc(double rs, double ld, double lq, double polesPairs, double magnetFlux, double inertia, double friction, double ts,
                     double brakeTorque,
                     DiscreteTimeTransformType_t transform) :
                     m_PMSMdq(rs, ld, lq, polesPairs, magnetFlux, inertia, friction, ts, brakeTorque, transform), m_elAnglePrev(0)
{

}

SDataVector STPMSMabc::execute(SDataVector in) // in have single inputs (slot) with three value va [0,0], vb [0,1] and vc [0,2]
{
    double va = in.data(0,0);
    double vb = in.data(0,1);
    //double vc = in.data(0,2);

    SDataVector vdq = m_abctodq.execute(SDataVector(va, vb, m_elAnglePrev));
    PMSMVars v = m_PMSMdq.execute(vdq);
    m_elAnglePrev = v.ElAngle;
    SDataVector idq = SDataVector(v.Id, v.Iq, m_elAnglePrev);
    SDataVector iabc = m_dqtoabc.execute(idq);

    return iabc;
}
