#include "stpmsmqd.h"

STPMSMqd::STPMSMqd(double rs, double ld, double lq, double polesPairs, double magnetFlux, double inertia, double friction, double ts,
                   double brakeTorque,
                   DiscreteTimeTransformType_t transform) :
    m_rs(rs), m_ld(ld), m_lq(lq), m_polesPairs(polesPairs), m_magneticFlux(magnetFlux), m_inertia(inertia), m_friction(friction), m_brakeTorque(brakeTorque),
    m_idPrev(0), m_iqPrev(0), m_wPrev(0), m_idIntTF(ts, transform), m_iqIntTF(ts, transform), m_wIntTF(ts, transform)
{
}

SDataVector STPMSMqd::execute(SDataVector in)
{
    double vd = in.data(0,0);
    double vq = in.data(0,1);

    double did = (vd - (m_rs * m_idPrev) + (m_polesPairs * m_wPrev * m_lq * m_iqPrev)) / m_ld;
    double diq = (vq - (m_rs * m_iqPrev) - (m_polesPairs * m_wPrev * m_ld * m_idPrev) - (m_polesPairs * m_wPrev * m_magneticFlux)) / m_lq;

    double id = m_idPrev = m_idIntTF.execute(SDataVector(did)).value();
    double iq = m_iqPrev = m_iqIntTF.execute(SDataVector(diq)).value();

    double torque = 1.5 * m_polesPairs * ((m_magneticFlux * iq) + ((m_ld - m_lq) * id * iq ));

    double dw = (torque - (m_friction * m_wPrev) - m_brakeTorque) / m_inertia;

    double w = m_wPrev = m_wIntTF.execute(SDataVector(dw)).value();

    SData d(0);
    d.append(id);
    d.append(iq);
    d.append(w);
    d.append(torque);
    return SDataVector(d);
}

PMSMVars::PMSMVars() : SDataVector()
{
}

PMSMVars::PMSMVars(SDataVector dv) : SDataVector(dv)
{
    Id = dv.data(0,0);
    Iq = dv.data(0,1);
    T = dv.data(0,2);
    Wm = dv.data(0,3);
}
