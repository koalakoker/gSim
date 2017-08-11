#ifndef SIMMODEL9_H
#define SIMMODEL9_H

#include "baseSimModel.h"
#include <QList>
#include "simModelElement.h"

class simModel9 : public baseSimModel
{
public:
    simModel9();

    /* Specific params for sim 9 */
    double m_pi_kp;
    double m_pi_ki;
    double m_pi_kd;
    double m_pi_n;

    double m_pp;
    double m_j;
    double m_f;

    bool m_wTetaPlot;
    bool m_torquePlot;

    QList<simModelElement*> m_values;

    void startSim(void);
};

#endif // SIMMODEL9_H
