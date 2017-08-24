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
//    double m_pi_kp;
//    double m_pi_ki;
//    double m_pi_kd;
//    double m_pi_n;

    double m_pp;
    double m_j;
    double m_f;
    double m_torque;

    bool m_wPlot;
    bool m_torquePlot;

    /********************* *********************/

public:
    simModel();
    void startSim(void);
};

#endif // SIMMODEL_H
