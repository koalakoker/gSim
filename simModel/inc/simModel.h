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
    double m_damping;
    // Input
    double m_targ;
    // State
    double m_yprev;
    double m_dyprev;

    void startSim(void);
};

#endif // SIMMODEL_H
