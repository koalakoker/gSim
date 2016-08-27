#ifndef STDQTOABC_H
#define STDQTOABC_H

#include "simulation/stransfer.h"

class STdqtoabc : public STransfer
{
public:
    STdqtoabc();

    SDataVector execute(SDataVector in);

private:
    double m_s23;
    double m_23p;
};

#endif // STDQTOABC_H
