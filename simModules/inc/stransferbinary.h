#ifndef STRANSFERBINARY_H
#define STRANSFERBINARY_H

#include "plot/selement.h"

class STransferBinary : public SElement
{
public:
    STransferBinary();

    virtual SDataVector execute(SDataVector in1, SDataVector in2) = 0;
};

#endif // STRANSFERBINARY_H
