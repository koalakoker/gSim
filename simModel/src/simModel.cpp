#include "simModel.h"

#include "smotormech.h"
#include "stpid.h"
#include "ssscope.h"

simModel::simModel()
{
    /* Set sim number */
    m_sim = 9;
    m_description = "Motor mechanical sim";

    /* Default common params */
    m_ts = 0.00005;
    m_tc = 0.00005;
    m_duration = 2;

    /********************* *********************/
    /*        Parameters initialization        */
    /********************* *********************/

    m_pi_kp = 3.0;
    m_pi_ki = 2.0;
    m_pi_kd = 0;
    m_pi_n = 0;

    m_pp = 4;
    m_j = 0.09;
    m_f = 0.05;

    m_wTetaPlot = true;
    m_torquePlot = false;

    /********************* *********************/

    /********************* *********************/
    /*      Setup parameters into the view     */
    /********************* *********************/

    m_userParams.append(new simModelElement("Motor parameters", SE_group, NULL));

    m_userParams.append(new simModelElement("Inertia", SE_double, (void*)(&m_j)));
    m_userParams.append(new simModelElement("Friction", SE_double, (void*)(&m_f)));
    m_userParams.append(new simModelElement("Poles pairs", SE_double, (void*)(&m_pp)));

    m_userParams.append(new simModelElement("PI parameters", SE_group, NULL));

    m_userParams.append(new simModelElement("Kp", SE_double, (void*)(&m_pi_kp)));
    m_userParams.append(new simModelElement("Ki", SE_double, (void*)(&m_pi_ki)));

    m_userParams.append(new simModelElement("Plot settings", SE_group, NULL));

    m_userParams.append(new simModelElement("wTetaPlot", SE_bool, (void*)(&m_wTetaPlot)));
    m_userParams.append(new simModelElement("torquePlot", SE_bool, (void*)(&m_torquePlot)));

    /********************* *********************/
}

void simModel::startSim(void)
{
    // Init sim vars
    m_t = 0;
    int m_step = (int)(m_duration / m_ts);
    int m_controlStepRatio = (int)(m_tc / m_ts);

    /********************* *********************/
    /* Define here the behaviour of your model */
    /********************* *********************/

    // Init sink-source-transfer
    SMotorMech motor(m_pp, m_j, m_f, m_ts);
    STPID speedpid(m_pi_kp, m_pi_ki, m_pi_kd, m_pi_n, m_tc);

    double speedTarg = 100;

    SDataVector tin;
    SSScope sscope("T",1);
    SSScope sscope2("Speed - Theta", 4);

    // Main cycle
    for (int i = 0; i < m_step; i++)
    {
        // Execution of sink and source

        if ((i % m_controlStepRatio) == 0)
        {
            // Execution of control cycle
            double err;
            err = speedTarg - motor.vars().Wm;
            tin = speedpid.execute(err);
        }

        motor.execute(tin);
        MotorMechVars iW = motor.vars();

        if (m_wTetaPlot)
        {
            sscope2.execute(m_t, SDataVector(iW.Wm, iW.MechAngle, iW.We, iW.ElAngle));
        }

        if (m_torquePlot)
        {
            sscope.execute(m_t, SDataVector(tin));
        }

        // Update of simutaion variables
        m_t += m_ts;

        // Update progress
        emit updateProgress((double)(i+1)/(double)m_step);
    }

    if (m_torquePlot)
    {
        sscope.scopeUpdate(m_ts);
    }

    if (m_wTetaPlot)
    {
        sscope2.scopeUpdate(m_ts);
    }

    /********************* *********************/
}
