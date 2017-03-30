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
    m_duration = 1;

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
    double k = 5.0;
    m_cruiseSpeed = (m_angleStep / m_movementDuration) * (1 + (1/k));

    m_t1 = m_movementDuration - (m_angleStep / m_cruiseSpeed);
    m_acceleration = m_cruiseSpeed / m_t1;

    m_teta0 = 0;
    m_teta1 = m_teta0 + (m_acceleration * m_t1 * m_t1) / 2;

    m_t2 = m_movementDuration - m_t1;
    m_teta2 = m_teta1 + (m_cruiseSpeed * (m_t2 - m_t1));

    m_omega = 0;
    m_teta = 0;

    // Init simulation vars
    m_t = 0;
    int m_step = (int)(m_duration / m_ts);

    // Init sink-source-transfer
    SSScope sscope("Angle",2);
    SSScope sscope1("Omega",1);

    //STPID stpid(PI_KP, PI_KI, 0, 0, m_tc, BackwardEuler);
    //STFIntegrator stfInt(m_tc, Trapezoidal);
    //STMotorMech motor(m_polesPairs, m_inertia, m_friction, m_ts, false);

    // Main cycle
    for (int i = 0; i < m_step; i++)
    {
        // Execution of sink and source

        /* Motor update */

//        /* Execute two torque steps */
//        if (m_t < 2.0)
//        {
//            m_torque = 1.0;
//        }
//        else
//        {
//            m_torque = -1.0;
//        }
//        motor.execute(m_torque);
//        MotorMechVars iW = motor.vars();

        double angle = 0;
        if (m_t < m_t1)
        {
            angle = m_teta0 + ((m_acceleration * m_t * m_t) / 2.0);
            m_omega += m_acceleration * m_ts;
        }
        else if (m_t < m_t2)
        {
            angle = m_teta1 + (m_cruiseSpeed * (m_t - m_t1));
        }
        else
        {
            double t = m_t - m_t2;
            angle = m_teta2 - ((m_acceleration * t * t) / 2.0) + (m_cruiseSpeed  * t);
            m_omega -= m_acceleration * m_ts;
        }
        m_teta += m_omega * m_ts;

        if (m_anglePlot)
        {
            sscope.execute(m_t, SDataVector(angle, m_teta));
            sscope1.execute(m_t, SDataVector(m_omega));
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
    }
}
