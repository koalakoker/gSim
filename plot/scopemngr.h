#ifndef SCOPEMNGR_H
#define SCOPEMNGR_H

#include <QList>
#include "ssscope.h"

class ScopeMngr
{
public:
    static ScopeMngr* Instance();
    void newScope(SSScope* pScope);
    SSScope* getScopeAt(int i);
    int scopeCount(void);

private:
    ScopeMngr();
    ScopeMngr(ScopeMngr const&);
    static ScopeMngr* m_pInstance;
    QList<SSScope*> m_scopes;
};

#endif // SCOPEMNGR_H
