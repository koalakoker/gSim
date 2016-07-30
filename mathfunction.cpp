#include "mathfunction.h"
#include "math.h"

mathFunction::mathFunction()
{

}

double mathFunction::calc(double t)
{
    double w = 2 * 3.14 * 3;
    double w2 = 2 * 3.14 * 8;
    return sin(w*t) + (0.3 * sin(w2*t));
}
