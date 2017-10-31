#include "simModel.h"

#include "stpmsmabc.h"
#include "stdpi.h"
//#include "stpid.h"
#include "ssscope.h"

simModel::simModel()
{
    /* Set sim number */
    m_sim = 11;
    m_description = "PMSM abc sim - Jiri";

    /* Default common params */
    m_ts = 0.0001;
    m_tc = 0.001;
    m_duration = 1;

    /********************* *********************/
    /*        Parameters initialization        */
    /********************* *********************/
    m_r = 0.35;
    m_l = 0.0006;
    m_pp = 2;

    double ke = 4;
    m_flux = (ke/m_pp) * (sqrt(2) / sqrt(3)) * (60/(1000*2*M_PI));

    m_j = 0.000005;
    m_f = 0.000014;

    double currBW = 6000;
    m_qd_kp = currBW * m_r;
    m_qd_ki = currBW * m_l;
    m_qd_kd = 0;
    m_qd_n = 0;

    double spdBW = 50;
    double spdAB = (1.5 * m_pp * m_flux) * (60 / (2 * M_PI));
    m_spd_kp = (spdBW * m_j)/ spdAB;
    m_spd_ki = (spdBW * m_f)/ spdAB;
    m_spd_kd = 0;
    m_spd_n = 0;

    m_brakeTorque = 0;

    m_abcCurrPlot = FALSE;
    m_angleSpeedPlot = TRUE;
    m_iqPlot = TRUE;
    m_vqdPlot = FALSE;

    /********************* *********************/

    /********************* *********************/
    /*      Setup parameters into the view     */
    /********************* *********************/

    m_userParams.append(new simModelElement("Motor parameters", SE_group, NULL));

    m_userParams.append(new simModelElement("Poles pairs", SE_double, (void*)(&m_pp)));
    m_userParams.append(new simModelElement("Stator Resistance", SE_double, (void*)(&m_r)));
    m_userParams.append(new simModelElement("Stator Inductance (d-q)", SE_double, (void*)(&m_l)));
    m_userParams.append(new simModelElement("Magnetic flux", SE_double, (void*)(&m_flux)));

    m_userParams.append(new simModelElement("Inertia",  SE_double, (void*)(&m_j), 6));
    m_userParams.append(new simModelElement("Friction", SE_double, (void*)(&m_f), 6));


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
    m_userParams.append(new simModelElement("vqd Plot", SE_bool, (void*)(&m_vqdPlot)));
}

#define RPMTORADS(rpm)  (((rpm)/60) * 2 * M_PI)
#define RADSTORPM(rads) (((rads)*60)/(2*M_PI))

void simModel::startSim(void)
{
    // Test specific initialization

    // Init sim vars
    m_t = 0;
    int m_step = (int)(m_duration / m_ts);
    int m_controlStepRatio = (int)(m_tc / m_ts);

    // Init sink-source-transfer

    STPMSMabc motor(m_r, m_l, m_l, m_pp, m_flux, m_j, m_f, m_ts, m_brakeTorque);
    STDPI idpid(m_qd_kp, m_qd_ki / m_ts , 24);
    STDPI iqpid(m_qd_kp, m_qd_ki / m_ts , 24);
    STDPI spdpid(m_spd_kp, m_spd_ki * m_tc, 3);
//    STPID idpid(m_qd_kp, m_qd_ki, 0, 0, m_ts);
//    STPID iqpid(m_qd_kp, m_qd_ki, 0, 0, m_ts);
//    STPID spdpid(m_spd_kp, m_spd_ki, 0, 0, m_tc);
    STabctodq abctodq;
    STdqtoabc dqtoabc;
    double idTarg = 0;
    double iqTarg = 0;
    double WmTarg = RPMTORADS(1000);//(1000/60) * 2 * M_PI;

    SSScope sscope("Iqd",4);
    SSScope sscope_speed("Speed", 1);
    SSScope sscope_teta("Theta", 1);
    SSScope sscope3("Vabc", 3);
    SSScope sscope4("Vqd", 2);

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
            //iqTarg = spdpid.execute(err).value();
            iqTarg = 1;
        }

        /* Park - Clark */
        SDataVector idq = abctodq.execute(SDataVector(motor.vars().Ia, motor.vars().Ib, motor.vars().ElAngle));

        id = idq.data(0, 0);
        iq = idq.data(0, 1);

        err = idTarg - id;
        vdin = idpid.execute(err);

        err = iqTarg - iq;
        vqin = iqpid.execute(err);

        if (m_vqdPlot)
        {
            sscope4.execute(m_t, SDataVector(vqin, vdin));
        }

        SDataVector vin = SDataVector(vdin, vqin, motor.vars().ElAngle);
        vin = dqtoabc.execute(vin);

        if (m_abcCurrPlot)
        {
            //sscope3.execute(m_t, vin);
            sscope3.execute(m_t, SDataVector(motor.vars().Ia, motor.vars().Ib, motor.vars().Ic));
        }

        motor.execute(vin);
        PMSMVars iW = motor.vars();
        if (m_iqPlot)
        {
            sscope.execute(m_t, SDataVector(iW.Iq,iW.Id, iqTarg, idTarg));
        }

        if (m_angleSpeedPlot)
        {
            sscope_speed.execute(m_t, SDataVector(RADSTORPM(iW.Wm)));
            sscope_teta.execute(m_t, SDataVector(iW.MechAngle));
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
        sscope_speed.scopeUpdate(m_ts);
        sscope_teta.scopeUpdate(m_ts);
    }

    if (m_abcCurrPlot)
    {
        sscope3.scopeUpdate(m_ts);
    }

    if (m_vqdPlot)
    {
        sscope4.scopeUpdate(m_ts);
    }
}
