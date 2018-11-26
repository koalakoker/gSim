#include "strc.h"

STRC::STRC(double r, double c, double ts)
{
    m_r = r;
    m_c = c;
    m_ts = ts;

    //m_a = r + (l * (2 / ts));
    //m_b = r - (l * (2 / ts));

    m_vPrev = 0;
    m_iPrev = 0;
}

SDataVector STRC::execute(SDataVector in)
{
    double i;

    //i = (in.value() + m_vPrev - (m_b * m_iPrev)) / m_a;

    m_vPrev = in.value();
    m_iPrev = i;

    return SDataVector(i);
}
