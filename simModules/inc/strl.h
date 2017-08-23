#ifndef STRL_H
#define STRL_H

#include "simmodules_global.h"

#include "stransfer.h"

class SIMMODULESSHARED_EXPORT STRL : public STransfer
{
public:
    STRL(double r, double l, double ts);

    SDataVector execute(SDataVector in);

private:
    double m_r;
    double m_l;
    double m_ts;

    double m_a;
    double m_b;

    double m_vPrev;
    double m_iPrev;
};

#endif // STRL_H
