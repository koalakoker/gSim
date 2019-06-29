#ifndef SSOURCE_H
#define SSOURCE_H

#include "plot/selement.h"


class SSource : public SElement
{
public:
    SSource();

    virtual SDataVector execute(double t) = 0;
};

#endif // SSOURCE_H
