#include "simModel.h"

#include "stpmsmabc.h"
#include "stpid.h"
#include "ssscope.h"

simModel::simModel()
{
    /* Set sim number */
    m_sim = 11;
    m_description = "PMSM abc sim - Jiri";

    /* Default common params */
    m_ts = 0.0001;
    m_tc = 0.001;
    m_duration = 0.3;

    /********************* *********************/
    /*        Parameters initialization        */
    /********************* *********************/
    m_qd_kp = 30;
    m_qd_ki = 20;
    m_qd_kd = 0;
    m_qd_n = 0;

    m_spd_kp = 0.4;
    m_spd_ki = 0.4;
    m_spd_kd = 0;
    m_spd_n = 0;

    m_r = 0.2;
    m_l = 0.0085;
    m_pp = 4;
    m_flux = 0.175;
    m_j = 0.089;
    m_f = 0.05;

    m_brakeTorque = 4;

    m_abcCurrPlot = TRUE;
    m_angleSpeedPlot = FALSE;
    m_iqPlot = TRUE;

    /********************* *********************/

    /********************* *********************/
    /*      Setup parameters into the view     */
    /********************* *********************/

    m_userParams.append(new simModelElement("Motor parameters", SE_group, NULL));

    m_userParams.append(new simModelElement("Poles pairs", SE_double, (void*)(&m_pp)));
    m_userParams.append(new simModelElement("Stator Resistance", SE_double, (void*)(&m_r)));
    m_userParams.append(new simModelElement("Stator Inductance (d-q)", SE_double, (void*)(&m_l)));
    m_userParams.append(new simModelElement("Inertia", SE_double, (void*)(&m_j)));
    m_userParams.append(new simModelElement("Friction", SE_double, (void*)(&m_f)));


    m_userParams.append(new simModelElement("Iqd PI parameters", SE_group, NULL));

    m_userParams.append(new simModelElement("Kp", SE_double, (void*)(&m_qd_kp)));
    m_userParams.append(new simModelElement("Ki", SE_double, (void*)(&m_qd_ki)));

    m_userParams.append(new simModelElement("Speed PI parameters", SE_group, NULL));

    m_userParams.append(new simModelElement("Kp", SE_double, (void*)(&m_spd_kp)));
    m_userParams.append(new simModelElement("Ki", SE_double, (void*)(&m_spd_ki)));

    m_userParams.append(new simModelElement("Load", SE_group, NULL));
    m_userParams.append(new simModelElement("Brake torque", SE_double, (void*)(&m_brakeTorque)));

    m_userParams.append(new simModelElement("Plot", SE_group, NULL));
    m_userParams.append(new simModelElement("abc Plot", SE_bool, (void*)(&m_abcCurrPlot)));
    m_userParams.append(new simModelElement("angle speed Plot", SE_bool, (void*)(&m_angleSpeedPlot)));
    m_userParams.append(new simModelElement("iqd Plot", SE_bool, (void*)(&m_iqPlot)));
}

void simModel::startSim(void)
{
    // Test specific initialization

    // Init sim vars
    m_t = 0;
    int m_step = (int)(m_duration / m_ts);
    int m_controlStepRatio = (int)(m_tc / m_ts);

    // Init sink-source-transfer

    STPMSMabc motor(m_r, m_l, m_l, m_pp, m_flux, m_j, m_f, m_ts, m_brakeTorque);
    STPID idpid(m_qd_kp, m_qd_ki, m_qd_kd, m_qd_n, m_tc);
    STPID iqpid(m_qd_kp, m_qd_ki, m_qd_kd, m_qd_n, m_tc);
    STPID spdpid(m_spd_kp, m_spd_ki, m_spd_kd, m_spd_n, m_tc);
    STabctodq abctodq;
    STdqtoabc dqtoabc;
    double idTarg = 0;
    double iqTarg = 4.76;
    double WmTarg = (1000/60) * 2 * M_PI;

    SSScope sscope("Iqd",2);
    SSScope sscope2("Speed - Theta", 4);
    SSScope sscope3("Vabc", 3);

    SDataVector vqin, vdin;

    // Main cycle
    for (int i = 0; i < m_step; i++)
    {
        // Execution of sink and source
        double id;
        double iq;
        double err;

        if ((i % m_controlStepRatio) == 0)
        {
            // Execution of control cycle
            err = WmTarg - motor.vars().Wm;
            iqTarg = spdpid.execute(err).value();
        }

        /* Park - Clark */
        SDataVector idq = abctodq.execute(SDataVector(motor.vars().Ia, motor.vars().Ib, motor.vars().ElAngle));

        id = idq.data(0, 0);
        iq = idq.data(0, 1);

        err = idTarg - id;
        vdin = idpid.execute(err);

        err = iqTarg - iq;
        vqin = iqpid.execute(err);

        SDataVector vin = SDataVector(vdin, vqin, motor.vars().ElAngle);
        vin = dqtoabc.execute(vin);

        if (m_abcCurrPlot)
        {
            sscope3.execute(m_t, vin);
        }

        motor.execute(vin);
        PMSMVars iW = motor.vars();
        if (m_iqPlot)
        {
            sscope.execute(m_t, SDataVector(iW.Iq,iW.Id));
        }

        if (m_angleSpeedPlot)
        {
            sscope2.execute(m_t, SDataVector(iW.Wm, iW.MechAngle, iW.We, iW.ElAngle));
        }

        // Update of simutaion variables
        m_t += m_ts;

        // Update progress
        emit updateProgress((double)(i+1)/(double)m_step);
    }

    if (m_iqPlot)
    {
        sscope.scopeUpdate(m_ts);
    }

    if (m_angleSpeedPlot)
    {
        sscope2.scopeUpdate(m_ts);
    }

    if (m_abcCurrPlot)
    {
        sscope3.scopeUpdate(m_ts);
    }
}
