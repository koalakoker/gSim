#include "stdemux.h"

STDemux::STDemux()
{

}

SDataVector STDemux::execute(SDataVector in)
{
    // SDataVector in is a 1,n input to be transformed in a n,1 output
    SData dataIn = in.data(0);
    SDataVector Out;
    SData newElem;
    int i = 0;
    foreach (double d, dataIn.data()) {
        newElem = SData(d);
        Out.append(newElem);
        i++;
    }

    return Out;
}
