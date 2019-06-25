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
    double m_fbrk;
    double m_wbrk;
    double m_fc;
    double m_f;

    double m_maxw;
    double m_acc;

    void startSim(void);
};

#endif // SIMMODEL_H
