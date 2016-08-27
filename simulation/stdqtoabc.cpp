#include "stdqtoabc.h"
#include "math.h"

STdqtoabc::STdqtoabc()
{
    m_s23 = sqrt(2/3);
    m_23p = 2 * M_PI / 3;
}

SDataVector STdqtoabc::execute(SDataVector in)
{
    double xd = in.data(0, 0);
    double xq = in.data(0, 1);
    double th = in.data(0, 2);

    double s = sin(th);
    double c = cos(th);
    double sm = sin(th - m_23p);
    double cm = cos(th - m_23p);
    double sp = sin(th + m_23p);
    double cp = cos(th + m_23p);

    double xa = (c * xd) - (s * xq);
    double xb = (cm * xd) - (sm * xq);
    double xc = (cp * xd) - (sp * xq);

    xa *= m_s23;
    xb *= m_s23;
    xc *= m_s23;

    return (SDataVector(xa, xb, xc));
}

