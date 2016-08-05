#include "sinfunction.h"
#include "math.h"

sinfunction::sinfunction()
{

}

double sinfunction::calc(double t)
{
    double a = 1;
    double f = 1;
    double w = 2 * 3.14 * f;
    return a * sin(w*t);
}
