#include "motormechvars.h"

MotorMechVars::MotorMechVars(SDataVector dv) : SDataVector(dv)
{
    Wm = dv.data(0,0);
    We = dv.data(0,1);
    MechAngle = dv.data(0,2);
    ElAngle = dv.data(0,3);
}

SDataVector MotorMechVars::toDataVector()
{
   return SDataVector(Wm, We, MechAngle, ElAngle);
}

