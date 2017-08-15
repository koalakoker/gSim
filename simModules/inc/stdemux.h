#ifndef STDEMUX_H
#define STDEMUX_H

#include "stransfer.h"

class STDemux : public STransfer
{
public:
    STDemux();

    SDataVector execute(SDataVector in);
};

#endif // STDEMUX_H
