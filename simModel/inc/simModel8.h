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
    double m_motSpeedRads;
    double m_exc_freq;
    double m_exc_ampl;
    double m_sin_att;
    double m_sin_delay;
    double m_sin_offset;
    double m_cos_att;
    double m_cos_delay;
    double m_cos_offset;

    /* Plots */
    bool excitingPlot;
    bool outputsPlot;
    bool thetaPlot;
    /********************* *********************/

public:
    simModel();
    void startSim(void);
};

#endif // SIMMODEL_H
