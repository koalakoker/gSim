#include "simulationModel9.h"
#include "simulationModules/ssscope.h"
#include "simulationModules/stfintegrator.h"
#include "simulationModules/stpid.h"
#include "simulationModules/stmotormech.h"
#include "simulationModules/stdelay.h"

simulationModel9::simulationModel9()
{
    /* Set simulation number */
    m_simulation = 9;
    m_description = "Position control simulation";

    /* Default common params */
    m_t = 0;
    m_ts = 0.0005;
    m_duration = 0.9;

    /* Specific params for simulation 9 */
    m_tc = m_ts;

    /* Motor deafult values */
    m_polesPairs = 4.0;
    m_inertia = 0.0010;
    m_friction = 0.0050;
    m_torque = 1.0;

    /* Plots */
    m_anglePlot = true;

    //
    PI_KP = 200.0;
    PI_KI = 10000.0000;

    m_movementDuration = m_duration;
    m_angleStep = 3.14;
}

void simulationModel9::startSimulation(void)
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
}
