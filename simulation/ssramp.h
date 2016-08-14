#ifndef SSRAMP_H
#define SSRAMP_H

#include "simulation/ssource.h"

class SSRamp : public SSource
{
public:
    SSRamp(double ramp = 1, double tStart = 0);

    SDataVector execute(double t);

    double tStart(){return m_tStart;}
    double ramp(){return m_ramp;}
    void setRamp(double ramp){m_ramp = ramp;}

private:
    double m_tStart;
    double m_ramp;
};

#endif // SSRAMP_H
