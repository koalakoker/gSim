#include "scopemngr.h"

ScopeMngr* ScopeMngr::m_pInstance = nullptr;

ScopeMngr::ScopeMngr()
{
}

ScopeMngr::ScopeMngr(ScopeMngr const&)
{
}

ScopeMngr* ScopeMngr::Instance()
{
   if (!m_pInstance)   // Only allow one instance of class to be generated.
      m_pInstance = new ScopeMngr;

   return m_pInstance;
}

void ScopeMngr::newScope(SSScope* pScope)
{
    m_scopes.append(pScope);
}

SSScope* ScopeMngr::getScopeAt(int i)
{
    return m_scopes.at(i);
}

int ScopeMngr::scopeCount(void)
{
    return m_scopes.count();
}
