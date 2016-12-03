#include "stpmsmdq.h"

STPMSMdq::STPMSMdq(double rs, double ld, double lq, double polesPairs, double magnetFlux, double inertia, double friction, double ts,
                   double brakeTorque,
                   DiscreteTimeTransformType_t transform) :
    m_rs(rs), m_ld(ld), m_lq(lq), m_polesPairs(polesPairs), m_magneticFlux(magnetFlux), m_inertia(inertia), m_friction(friction), m_brakeTorque(brakeTorque),
    m_idIntTF(ts, transform), m_iqIntTF(ts, transform), m_wIntTF(ts, transform), m_thIntTF(ts, transform)
{
}

void STPMSMdq::execute(SDataVector in)
{
    double vd = in.data(0,0);
    double vq = in.data(0,1);

    double id = m_vars.Id;
    double iq = m_vars.Iq;
    double wm = m_vars.Wm;

    double did = (vd - (m_rs * id) + (m_polesPairs * wm * m_lq * iq)) / m_ld;
    double diq = (vq - (m_rs * iq) - (m_polesPairs * wm * m_ld * id) - (m_polesPairs * wm * m_magneticFlux)) / m_lq;

    id = m_idIntTF.execute(did).value();
    iq = m_iqIntTF.execute(diq).value();

    double torque = 1.5 * m_polesPairs * ((m_magneticFlux * iq) + ((m_ld - m_lq) * id * iq ));

    double dw = (torque - (m_friction * wm) - m_brakeTorque) / m_inertia;

    wm = m_vars.Wm = m_wIntTF.execute(dw).value();

    double mechAngle = m_thIntTF.execute(wm).value();
    int p = (int)(mechAngle / (2 * M_PI));
    mechAngle -= p * (2 * M_PI);
    double elAngle = mechAngle * m_polesPairs;
    p = (int)(elAngle / (2 * M_PI));
    elAngle -= p * (2 * M_PI);

    m_vars.Id = id;
    m_vars.Iq = iq;
    m_vars.T = torque;
    m_vars.Wm = wm;
    m_vars.We = wm * m_polesPairs;
    m_vars.MechAngle = mechAngle;
    m_vars.ElAngle = elAngle;
}
