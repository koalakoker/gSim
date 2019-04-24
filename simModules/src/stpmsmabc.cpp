#include "stpmsmabc.h"

STPMSMabc::STPMSMabc(double rs, double ld, double lq, double polesPairs, double magnetFlux, double inertia, double friction, double ts,
                     double brakeTorque, double coggingToruqe, double coggingTorqueAngleDisplacement,
                     DiscreteTimeTransformType_t transform) :
                     m_PMSMdq(rs, ld, lq, polesPairs, magnetFlux,
                              inertia, friction, ts,
                              brakeTorque, coggingToruqe, coggingTorqueAngleDisplacement,
                              transform)
{

}

void STPMSMabc::execute(SDataVector in) // in have single inputs (slot) with three value va [0,0], vb [0,1] and vc [0,2]
{
    double va = in.data(0,0);
    double vb = in.data(0,1);
    //double vc = in.data(0,2);

    SDataVector vdq = m_abctodq.execute(SDataVector(va, vb, m_vars.ElAngle));
    m_PMSMdq.execute(vdq);
    m_vars = m_PMSMdq.vars();
    SDataVector idq = SDataVector(m_vars.Id, m_vars.Iq, m_vars.ElAngle);
    SDataVector iabc = m_dqtoabc.execute(idq);
    m_vars.Ia = iabc.data(0, 0);
    m_vars.Ib = iabc.data(0, 1);
    m_vars.Ic = iabc.data(0, 2);
}
