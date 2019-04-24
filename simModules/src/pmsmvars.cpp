#include "pmsmvars.h"

PMSMVars::PMSMVars(SDataVector dv) : SDataVector(dv)
{
    Ia =            dv.data(0,0);
    Ib =            dv.data(0,1);
    Id =            dv.data(0,2);
    Iq =            dv.data(0,3);
    T =             dv.data(0,4);
    coggingTorque = dv.data(0,5);
    Wm =            dv.data(0,6);
    We =            dv.data(0,7);
    MechAngle =     dv.data(0,8);
    ElAngle =       dv.data(0,9);
}

SDataVector PMSMVars::toDataVector()
{
   return SDataVector(Ia, Ib, Id, Iq, T, coggingTorque, Wm, We, MechAngle, ElAngle);
}

