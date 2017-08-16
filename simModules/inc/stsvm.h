#ifndef STSVM_H
#define STSVM_H

#include "simmodules_global.h"

#include "stransfer.h"

class SIMMODULESSHARED_EXPORT STSVM : public STransfer
{
public:
    STSVM();

    SDataVector execute(SDataVector in);
};

#endif // STSVM_H
