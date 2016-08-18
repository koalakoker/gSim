#include "stdpi.h"

STDPI::STDPI(double kp, double ki)
{
    m_kp = kp;
    m_ki = ki;

    m_intTerm = 0;
}

SDataVector STDPI::execute(SDataVector in)
{
    SDataVector Out;

    double u;
    double err = in.value();

    m_intTerm += m_ki * err;

    // Sat int term

    u = m_kp * err + m_intTerm;

    // Sat u

    Out.setValue(u);
    return Out;
}
