#include "stmux.h"

STMux::STMux()
{

}

SDataVector STMux::execute(SDataVector in)
{
    // SDataVector in is a n,1 input to be transformed in a 1,n output
    SData Data; // Create element data

    foreach (SData data, in.data()) {
        Data.append(data[0]);
    }

    SDataVector Out(1); // Create the single slot vector
    Out.setData(0, Data);

    return Out;
}
