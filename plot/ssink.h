#ifndef SSINK_H
#define SSINK_H

#include "selement.h"

class SSink : public SElement
{
public:
    SSink();

    virtual void execute(double t, SDataVector in) = 0;
};

#endif // SSINK_H
