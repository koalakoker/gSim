#include "simModel.h"
#include "ssscope.h"
#include "smotormech.h"
#include "stpid.h"

const double M_PI = 3.14159265359;

simModel::simModel()
{
    /* Set sim number */
    m_sim = 10;
    m_description = "Position control simulation";

    /* Default common params */
    m_ts = 0.0005;
    m_tc = m_ts;
    m_duration = 50;

    /********************* *********************/
    /*        Parameters initialization        */
    /********************* *********************/

    /* Motor */
    m_polesPairs = 7.0;
    m_inertia    = 0.0000044;
    m_friction   = 0.00002766;
    m_torque     = 0.013;

    m_motorTetaPlot  = true;
    m_motorOmegaPlot = false;

    /* Position PID */
    m_pi_kp = 0.0001;
    m_pi_ki = 0.0002;
    m_pi_kd = 0.00002;
    m_pi_n = 1;

    /* Plots */
    m_anglePlot = false;

    m_movementDuration = 50;
    m_angleStep = M_PI * 2;
    /********************* *********************/

    /********************* *********************/
    /*      Setup parameters into the view     */
    /********************* *********************/
    m_userParams.append(new simModelElement("Sim input parameters", SE_group, nullptr));
    m_userParams.append(new simModelElement("Duration (s)", SE_double,        static_cast<void*>(&m_movementDuration)));
    m_userParams.append(new simModelElement("AngleStep (rad)", SE_double,     static_cast<void*>(&m_angleStep)));
    m_userParams.append(new simModelElement("Plot", SE_bool,                  static_cast<void*>(&m_anglePlot)));
    m_userParams.append(new simModelElement("Sim output values", SE_group,    nullptr));
    m_userParams.append(new simModelElement("Jerk", SE_double,                static_cast<void*>(&m_jerk)));
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
    m_t7 = 9 * m_t1;

    m_jerk = m_angleStep / (12 * m_t1 * m_t1 * m_t1);
    m_cruiseSpeed = 2 * m_jerk * m_t1 * m_t1;

    m_omega = 0;
    m_teta = 0;
    m_acceleration = 0;

    // Init simulation vars
    m_t = 0;
    int m_step = static_cast<int>(m_duration / m_ts);
    /********************* *********************/
    /* Define here the behaviour of your model */
    /********************* *********************/

    // Init sink-source-transfer
    SMotorMech motor(m_polesPairs, m_inertia, m_friction, m_ts);
    STPID speedpid(m_pi_kp, m_pi_ki, m_pi_kd, m_pi_n, m_tc);
    double posTarg = M_PI / 2;
    SDataVector tin;

    SSScope sscope3("Motor - Speed");
    SSScope sscope4("Motor - Theta");

    SSScope sscope("Angle");
    SSScope sscope1("Omega");
    SSScope sscope2("Acceleration");

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
            m_acceleration = 0;
            m_omega = m_cruiseSpeed;
        }
        else if (m_t < m_t5)
        {
            jerk = -m_jerk;
        }
        else if (m_t < m_t6)
        {

        }
        else if (m_t < m_t7)
        {
            jerk = m_jerk;
        }
        else
        {
            m_acceleration = 0;
            m_omega = 0;
        }
        m_acceleration += jerk * m_ts;
        m_omega += m_acceleration * m_ts;
        m_teta += m_omega * m_ts;

        // Execution of control cycle
        posTarg = m_teta;
        double err;
        err = posTarg - motor.vars().MechAngle;
        tin = speedpid.execute(err);

        motor.execute(tin);
        MotorMechVars iW = motor.vars();

        if (m_motorOmegaPlot)
        {
            sscope3.execute(m_t, SDataVector(iW.Wm));
        }

        if (m_motorTetaPlot)
        {
            sscope4.execute(m_t, SDataVector(posTarg, iW.MechAngle));
        }

        if (m_anglePlot)
        {
            sscope.execute(m_t, SDataVector(m_teta));
            sscope1.execute(m_t, SDataVector(m_omega));
            sscope2.execute(m_t, SDataVector(m_acceleration));
        }

        // Update of simutaion variables
        m_t += m_ts;

        // Update progress
        emit updateProgress(static_cast<double>(i+1)/static_cast<double>(m_step));
    }

    if (m_motorOmegaPlot)
    {
        sscope3.scopeUpdate();
    }

    if (m_motorTetaPlot)
    {
        sscope4.scopeUpdate();
    }

    if (m_anglePlot)
    {
        sscope.scopeUpdate();
        sscope1.scopeUpdate();
        sscope2.scopeUpdate();
    }
    /********************* *********************/
}
