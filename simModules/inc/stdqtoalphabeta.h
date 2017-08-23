#ifndef STDQTOALPHABETA_H
#define STDQTOALPHABETA_H

#include "simmodules_global.h"

#include "stransfer.h"

class SIMMODULESSHARED_EXPORT STdqtoalphabeta : public STransfer
{
public:
    STdqtoalphabeta();

    SDataVector execute(SDataVector in);
};

#endif // STDQTOALPHABETA_H
