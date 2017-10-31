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
    double m_torque;
    double m_polesPairs;
    double m_inertia;
    double m_friction;

    double m_jerk;
    double m_acceleration;
    double m_cruiseSpeed;
    double m_angleStep;
    double m_movementDuration;

    double m_t1;
    double m_t2;
    double m_t3;
    double m_t4;
    double m_t5;
    double m_t6;
    double m_t7;

    double m_omega;
    double m_teta;

    /* Plots */
    bool m_anglePlot;

    /********************* *********************/
public:
    simModel();
    void startSim(void);
};

#endif // SIMMODEL_H
