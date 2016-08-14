#include "stdemux.h"

STDemux::STDemux()
{

}

SDataVector STDemux::execute(SDataVector in)
{
    // SDataVector in is a 1,n input to be transformed in a n,1 output
    SData dataIn = in.data(0);
    SDataVector* pOut = new SDataVector(dataIn.size()); // Create the multiple slot vector (size n)

    int i = 0;
    foreach (double d, dataIn.data()) {
        pOut->setData(i, 0, d);
        i++;
    }

    return *pOut;
}
