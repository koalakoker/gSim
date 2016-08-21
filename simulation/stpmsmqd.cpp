#include "stpmsmqd.h"

STPMSMqd::STPMSMqd(double rs, double ld, double lq, double polesPairs, double magnetFlux, double inertia, double friction, double brakeTorque) :
    m_rs(rs), m_ld(ld), m_lq(lq), m_polesPairs(polesPairs), m_magneticFlux(magnetFlux), m_inertia(inertia), m_friction(friction), m_brakeTorque(brakeTorque),
    m_idPrev(0), m_iqPrev(0), m_wPrev(0)
{
}

SDataVector STPMSMqd::execute(SDataVector in)
{
    SDataVector Out;

    double u;
    double vd = in.data(0,0);
    double vq = in.data(0,1);

    double did = (vd - (m_rs * m_idPrev) + (m_polesPairs * m_wPrev * m_lq * m_iqPrev)) / m_ld;
    double diq = (vq - (m_rs * m_iqPrev) - (m_polesPairs * m_wPrev * m_ld * m_idPrev) - (m_polesPairs * m_wPrev * m_magneticFlux)) / m_lq;

    Out.setValue(u);
    return Out;
}
