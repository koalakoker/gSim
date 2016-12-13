#include "stmotormech.h"

STMotorMech::STMotorMech(double polesPairs, double inertia, double friction, double ts, bool normalizeAngle,
                   double brakeTorque,
                   DiscreteTimeTransformType_t transform) :
    m_polesPairs(polesPairs), m_inertia(inertia), m_friction(friction),
    m_brakeTorque(brakeTorque), m_normalizeAngle(normalizeAngle),
    m_wIntTF(ts, transform), m_thIntTF(ts, transform)
{
}

void STMotorMech::execute(SDataVector in)
{
	  double torque = in.data(0,0);
    double wm = m_vars.Wm;
    double dw = (torque - (m_friction * wm) - m_brakeTorque) / m_inertia;

    wm = m_vars.Wm = m_wIntTF.execute(dw).value();

    double mechAngle = m_thIntTF.execute(wm).value();

    if (m_normalizeAngle)
    {
        int p = (int)(mechAngle / (2 * M_PI));
        mechAngle -= p * (2 * M_PI);
    }

    double elAngle = mechAngle * m_polesPairs;

    if (m_normalizeAngle)
    {
        int p = (int)(elAngle / (2 * M_PI));
        elAngle -= p * (2 * M_PI);
    }

    m_vars.Wm = wm;
    m_vars.We = wm * m_polesPairs;
    m_vars.MechAngle = mechAngle;
    m_vars.ElAngle = elAngle;
}
