#include "ssramp.h"

SSRamp::SSRamp(double ramp, double tStart)
{
    m_tStart = tStart;
    m_ramp = ramp;
}

SDataVector SSRamp::execute(double t)
{
    SDataVector Out;
    double y = 0;
    if (t > m_tStart)
    {
        y = m_ramp * (t - m_tStart);
    }
    Out.setData(0, 0, y);
    return Out;
}
