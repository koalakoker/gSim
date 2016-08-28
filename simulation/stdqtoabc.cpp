#include "stdqtoabc.h"
#include "math.h"

STdqtoabc::STdqtoabc()
{
    m_s3_2 = sqrt(3) / 2;
}

SDataVector STdqtoabc::execute(SDataVector in)
{
    double xd = in.data(0, 0);
    double xq = in.data(0, 1);
    double th = in.data(0, 2);

    double s = sin(th);
    double c = cos(th);

    double xa = (c * xd) - (s * xq);
    double xbeta = (s * xd) + (c * xq);

    double xb = ((-0.5) * xa) + ((m_s3_2) * xbeta);
    double xc = - xa - xb;

    return (SDataVector(xa, xb, xc));
}

