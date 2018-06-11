#include "simModel.h"

#include "smotormech.h"
#include "stpid.h"
#include "ssscope.h"
#include "math.h"

simModel::simModel()
{
    /* Set sim number */
    m_sim = 0; /* Dummy */
    m_description = "Mech - Position";

    /* Default common params */
    m_ts = 0.0001;
    m_tc = 0.001;
    m_duration = 10;

    /********************* *********************/
    /*        Parameters initialization        */
    /********************* *********************/
    m_pp = 2;
    m_j = 0.0005;
    m_f = 0.0014;
    m_brakeTorque = 0;
    m_maxTorque = 1;
    m_tetaTarg = 1;
    m_kp = 0.01;
    m_ki = 0.001;
    m_kd = 0.01;
    m_n = 100;
    m_anglePlot  = true;
    m_speedPlot  = true;
    m_torquePlot = true;

    /********************* *********************/

    /********************* *********************/
    /*      Setup parameters into the view     */
    /********************* *********************/

    m_userParams.append(new simModelElement("Motor parameters", SE_group, NULL));

    m_userParams.append(new simModelElement("Poles pairs", SE_double, (void*)(&m_pp)));

    m_userParams.append(new simModelElement("Inertia"   , SE_double, (void*)(&m_j), 6));
    m_userParams.append(new simModelElement("Friction"  , SE_double, (void*)(&m_f), 6));
    m_userParams.append(new simModelElement("Max torque", SE_double, (void*)(&m_maxTorque), 6));


    m_userParams.append(new simModelElement("Position PID parameters", SE_group, NULL));

    m_userParams.append(new simModelElement("Kp", SE_double, (void*)(&m_kp)));
    m_userParams.append(new simModelElement("Ki", SE_double, (void*)(&m_ki)));
    m_userParams.append(new simModelElement("Kd", SE_double, (void*)(&m_kd)));
    m_userParams.append(new simModelElement("n" , SE_double, (void*)(&m_n)));

//    m_userParams.append(new simModelElement("Load", SE_group, NULL));
//    m_userParams.append(new simModelElement("Brake torque", SE_double, (void*)(&m_brakeTorque)));
    m_userParams.append(new simModelElement("Target angle", SE_double, (void*)(&m_tetaTarg)));

    m_userParams.append(new simModelElement("Plot", SE_group, NULL));
    m_userParams.append(new simModelElement("angle Plot" , SE_bool, (void*)(&m_anglePlot)));
    m_userParams.append(new simModelElement("speed Plot" , SE_bool, (void*)(&m_speedPlot)));
    m_userParams.append(new simModelElement("torque Plot", SE_bool, (void*)(&m_torquePlot)));
}

#define RPMTORADS(rpm)  (((rpm)/60) * 2 * M_PI)
#define RADSTORPM(rads) (((rads)*60)/(2*M_PI))

void simModel::startSim(void)
{
    // Test specific initialization

    // Init sim vars
    m_t = 0;
    int m_step = (int)(m_duration / m_ts) + 2;
    int m_controlStepRatio = (int)(m_tc / m_ts);

    // Init sink-source-transfer

    SMotorMech motor(m_pp, m_j, m_f, m_ts);
    STPID pospid(m_kp, m_ki, m_kd, m_n, m_ts);
    pospid.m_maxOut = m_maxTorque;

    double torque = 0;

    SSScope sscope_speed("Speed");
    SSScope sscope_teta("Theta");
    SSScope sscope_torque("Torque");

    // Main cycle
    for (int i = 0; i < m_step; i++)
    {
        // Execution of sink and source
        double err;

        if ((i % m_controlStepRatio) == 0)
        {
            // Execution of control cycle

        }

        err = m_tetaTarg - motor.vars().MechAngle;
        torque = pospid.execute(err).value();

        motor.execute(SDataVector(torque));

        if (m_anglePlot)
        {
            sscope_teta.execute(m_t, SDataVector(motor.vars().MechAngle));
        }

        if (m_speedPlot)
        {
            sscope_speed.execute(m_t, SDataVector(RADSTORPM(motor.vars().Wm)));
        }

        if (m_torquePlot)
        {
            sscope_torque.execute(m_t, SDataVector(torque));
        }

        // Update of simutaion variables
        m_t += m_ts;

        // Update progress
        emit updateProgress((double)(i+1)/(double)m_step);
    }

    if (m_anglePlot)
    {
        sscope_teta.scopeUpdate();
        sscope_teta.exportData("scope_teta.txt");
    }

    if (m_speedPlot)
    {
        sscope_speed.scopeUpdate();
        sscope_speed.exportData("scope_speed.txt");
    }

    if (m_torquePlot)
    {
        sscope_torque.scopeUpdate();
        sscope_torque.exportData("scope_torque.txt");
    }
}
