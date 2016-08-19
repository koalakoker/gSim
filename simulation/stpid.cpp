#include "stpid.h"

STPID::STPID(double kp, double ki, double kd, double n, double ts, TransformType_t transform) :
    m_kp(kp), m_ki(ki), m_kd(kd), m_ts(ts), m_n(n)
{
    switch (transform)
    {
    case ForwardEuler:
    {
        // Using Forward Euler transform
        m_intTF = STFDiscreteFirstOrder(0, ts, -1);
        m_derTF = STFDiscreteFirstOrder(n, -n, -(1 - (n * ts))); // Filtered
    }
        break;
    default:
    case BackwardEuler:
    {
        // Using Backward Euler transform
        double temp = (1 + (n * ts));

        m_intTF = STFDiscreteFirstOrder(ts, 0, -1);
        m_derTF = STFDiscreteFirstOrder(n/temp, -n/temp, -1/temp); // Filtered
    }
        break;
    case Trapezoidal:
    {
        // Using Trapezoidal Euler transform
        double temp = (1 + (n * ts / 2));

        m_intTF = STFDiscreteFirstOrder(ts / 2, ts / 2, -1);
        m_derTF = STFDiscreteFirstOrder(n/temp, -n/temp, ((n * ts /2) - 1)/temp); // Filtered
    }
        break;
    }
}

SDataVector STPID::execute(SDataVector in)
{
    SDataVector Out;

    double u;
    double err = in.value();

    SDataVector errDV;
    errDV.setValue(err);
    u = (m_kp * err) + (m_ki * m_intTF.execute(errDV).value()) + (m_kd * m_derTF.execute(errDV).value());

    Out.setValue(u);
    return Out;
}
