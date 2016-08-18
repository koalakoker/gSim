#include "stpi.h"

STPI::STPI(double kp, double ki, double ts)
{
    m_kp = kp;
    m_ki = ki;
    m_ts = ts;

    m_a = kp + (ki * (ts / 2));
    m_b = (-kp) + (ki * (ts / 2));

    m_ePrev = 0;
    m_uPrev = 0;
}

SDataVector STPI::execute(SDataVector in)
{
    SDataVector Out;

    double u;

    u = m_uPrev + m_a * in.value() + m_b * m_ePrev;

    m_uPrev = u;
    m_ePrev = in.value();

    Out.setValue(u);
    return Out;
}
