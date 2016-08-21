#include "stfintegrator.h"

STFIntegrator::STFIntegrator(double ts, DiscreteTimeTransformType_t transform)
{
    switch (transform)
    {
    case ForwardEuler:
    {
        // Using Forward Euler transform
        m_intTF = STFDiscreteFirstOrder(0, ts, -1);
    }
        break;
    default:
    case BackwardEuler:
    {
        // Using Backward Euler transform
        m_intTF = STFDiscreteFirstOrder(ts, 0, -1);
    }
        break;
    case Trapezoidal:
    {
        // Using Trapezoidal Euler transform
        m_intTF = STFDiscreteFirstOrder(ts / 2, ts / 2, -1);
    }
        break;
    }
}

SDataVector STFIntegrator::execute(SDataVector in)
{
    return m_intTF.execute(in);
}

