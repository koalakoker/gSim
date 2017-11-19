#include "ssscope.h"

SSScope::SSScope(QString name, int tracks)
{
    m_wscope = new WScope(name, tracks);
    m_mwplot = new MWPlot();
}

void SSScope::execute(double t, SDataVector in)
{
    m_wscope->addPoint(t, in.data(0));
    m_mwplot->addPoint(t, in.data(0));
}

void SSScope::scopeUpdate(double dt)
{
    m_wscope->setdt(dt);
    m_wscope->show();
    m_wscope->refresh();
    m_wscope->maximizeX();
    m_wscope->maximizeY();
    m_mwplot->show();
}

void SSScope::exportData(QString fileName)
{
    m_wscope->exportData(fileName);
}
