#include "stfdiscretefirstorder.h"

STFDiscreteFirstOrder::STFDiscreteFirstOrder(double b0, double b1, double a1) : m_b0(b0), m_b1(b1), m_a1(a1), m_yPrev(0), m_xPrev(0)
{
}

SDataVector STFDiscreteFirstOrder::execute(SDataVector in)
{
    SDataVector Out;

    double y;
    double x = in.value();

    y = (m_b0 * x) + (m_b1 * m_xPrev) - (m_a1 * m_yPrev);

    m_yPrev = y;
    m_xPrev = x;

    Out.setValue(y);
    return Out;
}
