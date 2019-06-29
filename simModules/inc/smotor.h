#ifndef SMOTOR_H
#define SMOTOR_H

#include "simmodules_global.h"

#include "plot/selement.h"

class SIMMODULESSHARED_EXPORT SMotor : public SElement
{
public:
    SMotor();

    virtual void execute(SDataVector in) = 0;
};

#endif // SMOTOR_H
