#include "pmsmvars.h"

PMSMVars::PMSMVars(SDataVector dv) : SDataVector(dv)
{
    Ia = dv.data(0,0);
    Ib = dv.data(0,1);
    Id = dv.data(0,2);
    Iq = dv.data(0,3);
    T = dv.data(0,4);
    Wm = dv.data(0,5);
    We = dv.data(0,6);
    MechAngle = dv.data(0,7);
    ElAngle = dv.data(0,8);
}

SDataVector PMSMVars::toDataVector()
{
   return SDataVector(Ia, Ib, Id, Iq, T, Wm, We, MechAngle, ElAngle);
}

