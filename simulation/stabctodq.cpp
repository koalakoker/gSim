#include "stabctodq.h"
#include "math.h"

STabctodq::STabctodq()
{
    m_1_sq3 = 1 / sqrt(3);
}

SDataVector STabctodq::execute(SDataVector in)
{
    double xa = in.data(0, 0);
    double xb = in.data(0, 1);
    double th = in.data(0, 2);

    double xbeta = m_1_sq3 * (xa + (2 * xb));

    double s = sin(th);
    double c = cos(th);

    double xd = (c * xa) + (s * xbeta);
    double xq = (c * xbeta) - (s * xa);

    return SDataVector(xd, xq);
}
