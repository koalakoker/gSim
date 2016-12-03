#ifndef STDQTOABC_H
#define STDQTOABC_H

#include "simulationModules/stransfer.h"

class STdqtoabc : public STransfer
{
public:
    STdqtoabc();

    SDataVector execute(SDataVector in);

private:
    double m_s3_2;
};

#endif // STDQTOABC_H
