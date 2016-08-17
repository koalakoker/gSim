#include "stprev.h"

STPrev::STPrev()
{
}

SDataVector STPrev::execute(SDataVector in)
{
    SDataVector* pOut = new SDataVector();
    *pOut = m_prevValue;
    m_prevValue = in;
    return *pOut;
}
