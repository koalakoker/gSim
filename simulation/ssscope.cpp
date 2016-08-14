#include "ssscope.h"

SSScope::SSScope(int tracks)
{
    m_wscope = new WScope(tracks);
}

void SSScope::execute(double t, SDataVector in)
{
    m_wscope->addPoint(t, in.data(0));
}

void SSScope::scopeUpdate(double dt)
{
    m_wscope->setdt(dt);
    m_wscope->show();
    m_wscope->refresh();
}
