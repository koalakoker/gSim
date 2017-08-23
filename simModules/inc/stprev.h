#ifndef STPREV_H
#define STPREV_H

#include "simmodules_global.h"

#include "stransfer.h"

class SIMMODULESSHARED_EXPORT STPrev : public STransfer
{
public:
    STPrev();

    SDataVector execute(SDataVector in);

private:
    SDataVector m_prevValue;
};

#endif // STPREV_H
