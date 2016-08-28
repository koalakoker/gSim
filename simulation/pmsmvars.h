#ifndef PMSMVARS_H
#define PMSMVARS_H

#include "simulation/sdatavector.h"

class PMSMVars : public SDataVector
{
public:
    PMSMVars();
    PMSMVars(SDataVector dv);

    SDataVector toDataVector();

    double Ia;
    double Ib;
    double Iq;
    double Id;
    double T;
    double Wm;
    double We;
    double MechAngle;
    double ElAngle;
};

#endif // PMSMVARS_H
