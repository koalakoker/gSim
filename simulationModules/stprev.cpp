#include "stprev.h"

STPrev::STPrev()
{
    m_prevValue = SDataVector(0);
}

SDataVector STPrev::execute(SDataVector in)
{
    SDataVector Out;
    Out = m_prevValue;
    m_prevValue = in;
    return Out;
}
