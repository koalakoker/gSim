#ifndef STDEMUX_H
#define STDEMUX_H

#include "simmodules_global.h"

#include "stransfer.h"

class SIMMODULESSHARED_EXPORT STDemux : public STransfer
{
public:
    STDemux();

    SDataVector execute(SDataVector in);
};

#endif // STDEMUX_H
