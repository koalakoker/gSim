#include "ssscope.h"

SSScope::SSScope(QString name, int tracks)
{
    m_wscope = new WScope(name, tracks);
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
    m_wscope->maximizeX();
    m_wscope->maximizeY();
}

void SSScope::exportData(QString fileName)
{
    m_wscope->exportData(fileName);
}
