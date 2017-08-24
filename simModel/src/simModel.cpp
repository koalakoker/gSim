#include "simModel.h"
#include "ssscope.h"

simModel::simModel()
{
    /* Set sim number */
    m_sim = 10;
    m_description = "Position control simulation";

    /* Default common params */
    m_ts = 0.0005;
    m_tc = m_ts;
    m_duration = 0.026;

    /********************* *********************/
    /*        Parameters initialization        */
    /********************* *********************/
    m_polesPairs = 4.0;
    m_inertia = 0.0010;
    m_friction = 0.0050;
    m_torque = 1.0;

    /* Plots */
    m_anglePlot = true;

    m_movementDuration = m_duration;
    m_angleStep = 4.92;
    /********************* *********************/

    /********************* *********************/
    /*      Setup parameters into the view     */
    /********************* *********************/
    m_userParams.append(new simModelElement("Sim input parameters", SE_group, NULL));
    m_userParams.append(new simModelElement("Duration (s)", SE_double, (void*)(&m_movementDuration)));
    m_userParams.append(new simModelElement("AngleStep (rad)", SE_double, (void*)(&m_angleStep)));
    m_userParams.append(new simModelElement("Plot", SE_bool, (void*)(&m_anglePlot)));
    m_userParams.append(new simModelElement("Sim output values", SE_group, NULL));
    m_userParams.append(new simModelElement("Jerk", SE_double, (void*)(&m_jerk)));
    /********************* *********************/
}

void simModel::startSim(void)
{
    // Test specific initialization
    m_t1 = m_movementDuration / 9;
    m_t2 = 2 * m_t1;
    m_t3 = 3 * m_t1;
    m_t4 = 6 * m_t1;
    m_t5 = 7 * m_t1;
    m_t6 = 8 * m_t1;

    m_jerk = m_angleStep / (12 * m_t1 * m_t1 * m_t1);
    m_cruiseSpeed = 2 * m_jerk * m_t1 * m_t1;

    m_omega = 0;
    m_teta = 0;
    m_acceleration = 0;

    // Init simulation vars
    m_t = 0;
    int m_step = (int)(m_duration / m_ts);
    /********************* *********************/
    /* Define here the behaviour of your model */
    /********************* *********************/

    // Init sink-source-transfer
    SSScope sscope("Angle",1);
    SSScope sscope1("Omega",1);
    SSScope sscope2("Acceleration",1);

    // Main cycle
    for (int i = 0; i < m_step; i++)
    {
        // Execution of sink and source

        double jerk = 0;
        /* Motor update */
        if (m_t < m_t1)
        {
            jerk = m_jerk;
        }
        else if (m_t < m_t2)
        {
        }
        else if (m_t < m_t3)
        {
            jerk = -m_jerk;
        }
        else if (m_t < m_t4)
        {

        }
        else if (m_t < m_t5)
        {
            jerk = -m_jerk;
        }
        else if (m_t < m_t6)
        {

        }
        else
        {
            jerk = m_jerk;
        }
        m_acceleration += jerk * m_ts;
        m_omega += m_acceleration * m_ts;
        m_teta += m_omega * m_ts;

        if (m_anglePlot)
        {
            sscope.execute(m_t, SDataVector(m_teta));
            sscope1.execute(m_t, SDataVector(m_omega));
            sscope2.execute(m_t, SDataVector(m_acceleration));
        }

        // Update of simutaion variables
        m_t += m_ts;

        // Update progress
        emit updateProgress((double)(i+1)/(double)m_step);
    }

    if (m_anglePlot)
    {
        sscope.scopeUpdate(m_ts);
        sscope1.scopeUpdate(m_ts);
        sscope2.scopeUpdate(m_ts);
    }
    /********************* *********************/
}
