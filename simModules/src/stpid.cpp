#include "stpid.h"

STPID::STPID(double kp, double ki, double kd, double n, double ts, DiscreteTimeTransformType_t transform) :
    m_kp(kp), m_ki(ki), m_kd(kd), m_intTF(ts, transform), m_derTF(ts, n, transform)
{
    m_maxOut = 1000000;
    m_maxIntTerm = m_maxOut;
}

SDataVector STPID::execute(SDataVector in)
{
    double u;
    double err = in.value();

    double intTerm = m_ki * m_intTF.execute(err).value();
    u = (m_kp * err) + (intTerm) + (m_kd * m_derTF.execute(err).value());

    if (u > m_maxOut)
    {
        u = m_maxOut;
    }

    if (u < -m_maxOut)
    {
        u = -m_maxOut;
    }

    return SDataVector(u);
}
