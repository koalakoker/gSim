#ifndef STPREV_H
#define STPREV_H

#include "simModules/stransfer.h"

class STPrev : public STransfer
{
public:
    STPrev();

    SDataVector execute(SDataVector in);

private:
    SDataVector m_prevValue;
};

#endif // STPREV_H
