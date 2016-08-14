#include "math.h"
#include "sssin.h"

SSSin::SSSin()
{

}

SDataVector SSSin::execute(double t)
{
    SDataVector* pOut = new SDataVector();
    double y = m_amplitude * sin(2 * M_PI * m_frequency * t);
    pOut->setData(0, 0, y);
    return *pOut;
}
