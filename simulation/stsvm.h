#ifndef STSVM_H
#define STSVM_H

#include "stransfer.h"

class STSVM : public STransfer
{
public:
    STSVM();

    SDataVector execute(SDataVector in);
};

#endif // STSVM_H
