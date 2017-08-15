#include "stdqtoalphabeta.h"
#include <math.h>

STdqtoalphabeta::STdqtoalphabeta()
{

}

SDataVector STdqtoalphabeta::execute(SDataVector in)
{
    double xd = in.data(0, 0);
    double xq = in.data(0, 1);
    double th = in.data(0, 2);

    double s = sin(th);
    double c = cos(th);

    double xalpha = (c * xd) - (s * xq);
    double xbeta = (s * xd) + (c * xq);

    return (SDataVector(xalpha, xbeta));
}


