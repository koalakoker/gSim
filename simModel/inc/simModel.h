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

    /* Specific params for sim */
    double m_rs;
    double m_ls;
    double m_flux;

    double m_polesPairs;
    double m_inertia;
    double m_friction;

    double m_pi_iqd_bw;
    double m_pi_iqd_kp;
    double m_pi_iqd_ki;
    double m_pi_iqd_kd;
    double m_pi_iqd_n;

    double m_pi_speed_bw;
    double m_pi_speed_kp;
    double m_pi_speed_ki;
    double m_pi_speed_kd;
    double m_pi_speed_n;

    void startSim(void);
};

#endif // SIMMODEL_H
