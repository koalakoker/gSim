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
    // Params
    double m_naturalfreq;
    double m_wd;
    double m_th;
    double m_k;
    double m_damping;
    // Input
    double m_acc;
    double m_omega;
    double m_teta;
    // State
    double m_yprev;
    double m_dyprev;

    // PLL
    // Params
    double m_pllKp;
    double m_pllKi;
    double m_tetaEst;

    void startSim(void);
};

#endif // SIMMODEL_H
