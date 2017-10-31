#include "stdpi.h"

STDPI::STDPI(double kp, double ki, double sat) :
    m_kp(kp), m_ki(ki), m_sat(sat), m_intTerm(0)
{
}

SDataVector STDPI::execute(SDataVector in)
{
    double u;
    double err = in.value();

    m_intTerm += m_ki * err;

    // Sat int term

    u = (m_kp * err) + m_intTerm;

    // Sat u
    if (u > m_sat)
    {
        u = m_sat;
    } else if (u < -m_sat)
    {
        u = -m_sat;
    }

    return SDataVector(u);
}
