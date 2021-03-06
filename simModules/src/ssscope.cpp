#include "ssscope.h"

SSScope::SSScope(QString name)
{
    m_mwplot = new MWPlot(name);
}

void SSScope::execute(double t, SDataVector in)
{
    m_mwplot->addPoint(t, in.data(0));
}

void SSScope::scopeUpdate(void)
{
    m_mwplot->show();
    m_mwplot->updatePlot();
}

void SSScope::exportData(QString fileName)
{
    m_mwplot->exportData(fileName);
}
