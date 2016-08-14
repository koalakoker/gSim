#ifndef SSSIN_H
#define SSSIN_H

#include "ssource.h"

class SSSin : public SSource
{
public:
    SSSin();

    SDataVector execute(double t, SDataVector in);
};

#endif // SSSIN_H
