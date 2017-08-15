#ifndef STMUX_H
#define STMUX_H

#include "stransfer.h"

class STMux : public STransfer
{
public:
    STMux();

    SDataVector execute(SDataVector in);
};

#endif // STMUX_H
