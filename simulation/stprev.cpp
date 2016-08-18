#include "stprev.h"

STPrev::STPrev()
{
}

SDataVector STPrev::execute(SDataVector in)
{
    SDataVector Out;
    Out = m_prevValue;
    m_prevValue = in;
    return Out;
}
