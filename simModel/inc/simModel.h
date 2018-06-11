#ifndef SIMMODEL_H
#define SIMMODEL_H

#include "gsimmodel_global.h"
#include"baseSimModel.h"

class GSIMMODELSHARED_EXPORT simModel : public baseSimModel
{
private:
    /********************* *********************/
    /*   Add here parameters for simulation    */
    /********************* *********************/

    /********************* *********************/

public:
    simModel();

    double m_kp;
    double m_ki;
    double m_kd;
    double m_n;

    double m_pp;
    double m_j;
    double m_f;

    double m_maxTorque;
    double m_brakeTorque;

    double m_tetaTarg;

    bool m_anglePlot;
    bool m_speedPlot;
    bool m_torquePlot;

    void startSim(void);
};

#endif // SIMMODEL_H
