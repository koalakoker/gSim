#ifndef STABCTODQ_H
#define STABCTODQ_H

#include "simulation/stransfer.h"

class STabctodq : public STransfer
{
public:
    STabctodq();

    SDataVector execute(SDataVector in);

private:
    double m_1_sq3;
};

#endif // STABCTODQ_H
