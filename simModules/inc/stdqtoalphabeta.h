#ifndef STDQTOALPHABETA_H
#define STDQTOALPHABETA_H

#include "stransfer.h"

class STdqtoalphabeta : public STransfer
{
public:
    STdqtoalphabeta();

    SDataVector execute(SDataVector in);
};

#endif // STDQTOALPHABETA_H
