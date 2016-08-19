#include "stpid.h"

STPID::STPID(double kp, double ki, double kd, double n, double ts, TransformType_t transform) :
    m_kp(kp), m_ki(ki), m_kd(kd), m_ts(ts), m_n(n)
{
    switch (transform)
    {
    default:
    case BackwardEuler:
    {
        // Using Backward Euler transform
        double temp = (1 + (n * ts));

        m_intTF = STFDiscreteFirstOrder(ts, 0, -1);
        m_derTF = STFDiscreteFirstOrder(n/temp, -n/temp, -1/temp); // Filtered
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
