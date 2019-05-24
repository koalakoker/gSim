#include "ssscope.h"
#include "scopemngr.h"

SSScope::SSScope(QString name, QVector<QWidget *> *pScopes)
{
    m_mwplot = new PlotterWindow(name);
    if (pScopes)
    {
        pScopes->append(m_mwplot);
    }
}

void SSScope::execute(double t, SDataVector in)
{
    m_mwplot->addPoint(t, in.data(0));
}

void SSScope::scopeUpdate(void)
{
    int displacement = 30;
    ScopeMngr::Instance()->newScope(this);
    int i = ScopeMngr::Instance()->scopeCount();
    m_mwplot->show();
    m_mwplot->createPlot();
    m_mwplot->move((i-1) * displacement,(i-1) * displacement);
}

void SSScope::exportData(QString fileName)
{
    m_mwplot->exportData(fileName);
}
