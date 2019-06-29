#ifndef MOTORMECHVARS_H
#define MOTORMECHVARS_H

#include "simmodules_global.h"

#include "plot/sdatavector.h"

class SIMMODULESSHARED_EXPORT MotorMechVars : public SDataVector
{
public:
    MotorMechVars() : SDataVector(), Wm(0), We(0), MechAngle(0), ElAngle(0) {}
    MotorMechVars(SDataVector dv);

    SDataVector toDataVector();

    double Wm;
    double We;
    double MechAngle;
    double ElAngle;
};

#endif // MOTORMECHVARS_H
