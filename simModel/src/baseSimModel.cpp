#include "baseSimModel.h"

baseSimModel::baseSimModel()
{
    /* Set sim number */
    m_sim = 0;
    m_description = "";

    /* Default common params */
    m_t = 0;
    m_ts = 0.00005;
    m_tc = 0.00005;
    m_duration = 0.02;
}

void baseSimModel::startSim(void) {}

void baseSimModel::closeScopes(void)
{
    for (int i = 0; i < m_scopes.size(); ++i)
    {
        m_scopes.at(i)->close();
    }
}
