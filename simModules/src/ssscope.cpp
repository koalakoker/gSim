#include "ssscope.h"

SSScope::SSScope(QString name)
{
    m_wplot = new WPlot();
    m_wplot->setWindowTitle(name);
}

void SSScope::execute(double t, SDataVector in)
{
    m_wplot->addPoint(t, in.data(0));
}

void SSScope::scopeUpdate(void)
{
    m_wplot->show();
    m_wplot->createPlot();
}

void SSScope::exportData(QString fileName)
{
    m_wplot->saveData(fileName);
    //m_wplot->exportData(fileName);
}
