#include "math.h"
#include "sssincos.h"

SSSinCos::SSSinCos(trigType_t trigType, double amplitude, double frequency)
{
    m_trigType = trigType;
    m_amplitude = amplitude;
    m_frequency = frequency;
}

SDataVector SSSinCos::execute(double t)
{
    SDataVector* pOut = new SDataVector();
    double y = m_amplitude;
    double w = 2 * M_PI * m_frequency * t;
    if (m_trigType == sinType)
    {
        y *= sin(w);
    }
    else
    {
        y *= cos(w);
    }
    pOut->setData(0, 0, y);
    return *pOut;
}
