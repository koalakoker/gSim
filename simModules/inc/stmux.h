#ifndef STMUX_H
#define STMUX_H

#include "simmodules_global.h"

#include "stransfer.h"

class SIMMODULESSHARED_EXPORT STMux : public STransfer
{
public:
    STMux();

    SDataVector execute(SDataVector in);
};

#endif // STMUX_H
