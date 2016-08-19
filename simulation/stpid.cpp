#include "stpid.h"

STPID::STPID(double kp, double ki, double kd, double n, double ts, TransformType_t transform)
{
    m_kp = kp;
    m_ki = ki;
    m_kd = kd;
    m_ts = ts;
    m_n = n;

    switch (transform)
    {
    default:
    case BackwardEuler:
    {
        // Using Backward Euler transform
        double temp = (1 + (n * ts));
        m_a0 = ((kp * temp) + (ki * ts  * temp) + (kd * n)) /  temp;
        m_a1 = -(((2 * kd * n) + (kp * (2 + (n * ts))) + (ki * ts)) / temp);
        m_a2 = (kp + (kd * n)) / temp;
        m_b1 = (2 + (n * ts)) / temp;
        m_b2 = -((1) / temp);
    }
        break;
    }

    m_ePrev = 0;
    m_e2Prev = 0;
    m_uPrev = 0;
    m_u2Prev = 0;
}

SDataVector STPID::execute(SDataVector in)
{
    SDataVector Out;

    double u;
    double err = in.value();

    u = (m_b1 * m_uPrev) + (m_b2 * m_u2Prev) + (m_a0 * err) + (m_a1 * m_ePrev) + (m_a2 * m_e2Prev);

    m_u2Prev = m_uPrev;
    m_e2Prev = m_ePrev;
    m_uPrev = u;
    m_ePrev = err;

    Out.setValue(u);
    return Out;
}
