#include "pmsmvars.h"

PMSMVars::PMSMVars() : SDataVector()
{
}

PMSMVars::PMSMVars(SDataVector dv) : SDataVector(dv)
{
    Id = dv.data(0,0);
    Iq = dv.data(0,1);
    T = dv.data(0,2);
    Wm = dv.data(0,3);
    We = dv.data(0,4);
    MechAngle = dv.data(0,5);
    ElAngle = dv.data(0,6);
}

SDataVector PMSMVars::toDataVector()
{
   return SDataVector(Id, Iq, T, Wm, We, MechAngle, ElAngle);
}

