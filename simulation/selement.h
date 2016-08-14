#ifndef SELEMENT_H
#define SELEMENT_H

#include "sdatavector.h"

class SElement
{
public:
    SElement();

    virtual SDataVector execute(double t, SDataVector in) = 0;
};

#endif // SELEMENT_H
