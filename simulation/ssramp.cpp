#include "ssramp.h"

SSRamp::SSRamp(double ramp, double tStart)
{
    m_tStart = tStart;
    m_ramp = ramp;
}

SDataVector SSRamp::execute(double t)
{
    SDataVector* pOut = new SDataVector();
    double y = 0;
    if (t > m_tStart)
    {
        y = m_ramp * (t - m_tStart);
    }
    pOut->setData(0, 0, y);
    return *pOut;
}
