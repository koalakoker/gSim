#include "stdpid.h"

STDPID::STDPID(double kp, double ki, double kd, double dt, double sat) :
    m_kp(kp), m_ki(ki), m_kd(kd), m_dt(dt), m_sat(sat), m_intTerm(0)
{
}

SDataVector STDPID::execute(SDataVector in)
{
    double u;
    double err = in.value();

    if (m_ki != 0.0)
    {
        m_intTerm += m_ki * err * m_dt;
    }
    else
    {
        m_intTerm = 0.0;
    }

    // Sat int term

    u = (m_kp * err) + m_intTerm + (m_kd * (err - m_prev_err) / m_dt);
    m_prev_err = err;

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
