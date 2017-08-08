#ifndef PMSMVARS_H
#define PMSMVARS_H

#include "simModules/sdatavector.h"

class PMSMVars : public SDataVector
{
public:
    PMSMVars() : SDataVector(), Ia(0), Ib(0), Iq(0), Id(0), T(0), Wm(0), We(0), MechAngle(0), ElAngle(0) {}
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
