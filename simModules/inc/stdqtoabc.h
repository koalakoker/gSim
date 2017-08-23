#ifndef STDQTOABC_H
#define STDQTOABC_H

#include "simmodules_global.h"

#include "stransfer.h"

class SIMMODULESSHARED_EXPORT STdqtoabc : public STransfer
{
public:
    STdqtoabc();

    SDataVector execute(SDataVector in);

private:
    double m_s3_2;
};

#endif // STDQTOABC_H
