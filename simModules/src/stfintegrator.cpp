#include "stfintegrator.h"

STFIntegrator::STFIntegrator(double ts, double startingValue, DiscreteTimeTransformType_t transform)
{
    switch (transform)
    {
    case ForwardEuler:
    {
        // Using Forward Euler transform
        m_intTF = STFDiscreteFirstOrder(0, ts, -1, startingValue);
    }
        break;
    default:
    case BackwardEuler:
    {
        // Using Backward Euler transform
        m_intTF = STFDiscreteFirstOrder(ts, 0, -1, startingValue);
    }
        break;
    case Trapezoidal:
    {
        // Using Trapezoidal Euler transform
        m_intTF = STFDiscreteFirstOrder(ts / 2, ts / 2, -1, startingValue);
    }
        break;
    }
}

SDataVector STFIntegrator::execute(SDataVector in)
{
    return m_intTF.execute(in);
}

