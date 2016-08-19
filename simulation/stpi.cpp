#include "stpi.h"

STPI::STPI(double kp, double ki, double ts, TransformType_t transform)
{
    m_kp = kp;
    m_ki = ki;
    m_ts = ts;

    switch (transform)
    {
    default:
    case BackwardEuler:
    {
        // Using Backward Euler transform
        m_a = kp + (ki * ts );
        m_b = -kp;
    }
        break;
    case Trapezoidal:
    {
        // using Trapezoidal transform
        m_a = kp + (ki * (ts / 2));
        m_b = (-kp) + (ki * (ts / 2));
    }
        break;
    }

    m_ePrev = 0;
    m_uPrev = 0;
}

SDataVector STPI::execute(SDataVector in)
{
    SDataVector Out;

    double u;
    double err = in.value();

    u = m_uPrev + m_a * err + m_b * m_ePrev;

    m_uPrev = u;
    m_ePrev = err;

    Out.setValue(u);
    return Out;
}
