#ifndef SMOTOR_H
#define SMOTOR_H

#include "selement.h"

class SMotor : public SElement
{
public:
    SMotor();

    virtual void execute(SDataVector in) = 0;
};

#endif // SMOTOR_H
