#include "stpid.h"

STPID::STPID(double kp, double ki, double kd, double n, double ts, DiscreteTimeTransformType_t transform) :
    m_kp(kp), m_ki(ki), m_kd(kd), m_intTF(ts, transform), m_derTF(ts, n, transform)
{
}

SDataVector STPID::execute(SDataVector in)
{
    double u;
    double err = in.value();

    u = (m_kp * err) + (m_ki * m_intTF.execute(err).value()) + (m_kd * m_derTF.execute(err).value());

    return SDataVector(u);
}
