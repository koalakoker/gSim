#include "stmux.h"

STMux::STMux()
{

}

SDataVector STMux::execute(SDataVector in)
{
    // SDataVector in is a n,1 input to be transformed in a 1,n output
    SData* pData = new SData(0); // Create element data

    foreach (SData data, in.data()) {
        pData->append(data[0]);
    }

    SDataVector* pOut = new SDataVector(1); // Create the single slot vector
    pOut->setData(0, *pData);

    return *pOut;
}
