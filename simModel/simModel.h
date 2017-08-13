#ifndef SIMMODEL_H
#define SIMMODEL_H

#include "gsimmodel_global.h"
#include"simTemplates/simModel/baseSimModel.h"

class GSIMMODELSHARED_EXPORT simModel : public baseSimModel
{
private:
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

public:
    simModel();
    void startSim(void);
};

#endif // SIMMODEL_H
