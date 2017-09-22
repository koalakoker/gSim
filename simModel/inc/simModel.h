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

    /* Specific params for sim 7 */
    double m_qd_kp;
    double m_qd_ki;
    double m_qd_kd;
    double m_qd_n;

    double m_spd_kp;
    double m_spd_ki;
    double m_spd_kd;
    double m_spd_n;

    double m_r;
    double m_l;
    double m_flux;

    double m_pp;
    double m_j;
    double m_f;

    double m_brakeTorque;

    bool m_abcCurrPlot;
    bool m_angleSpeedPlot;
    bool m_iqPlot;

    void startSim(void);
};

#endif // SIMMODEL_H
