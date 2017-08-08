#include "stfderivatorfitered.h"

STFDerivatorFitered::STFDerivatorFitered(double ts, double n, DiscreteTimeTransformType_t transform)
{
    switch (transform)
    {
    case ForwardEuler:
    {
        // Using Forward Euler transform
        m_derTF = STFDiscreteFirstOrder(n, -n, -(1 - (n * ts))); // Filtered
    }
        break;
    default:
    case BackwardEuler:
    {
        // Using Backward Euler transform
        double temp = (1 + (n * ts));
        m_derTF = STFDiscreteFirstOrder(n/temp, -n/temp, -1/temp); // Filtered
    }
        break;
    case Trapezoidal:
    {
        // Using Trapezoidal Euler transform
        double temp = (1 + (n * ts / 2));
        m_derTF = STFDiscreteFirstOrder(n/temp, -n/temp, ((n * ts /2) - 1)/temp); // Filtered
    }
        break;
    }
}

SDataVector STFDerivatorFitered::execute(SDataVector in)
{
    return m_derTF.execute(in);
}
