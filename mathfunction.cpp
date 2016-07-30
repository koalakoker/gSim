#include "mathfunction.h"
#include "math.h"

mathFunction::mathFunction()
{

}

double mathFunction::calc(double t)
{
    double w = 2 * 3.14 * 3;
    return sin(w*t);
}
