#include "simModel.h"

#include "stpmsmabc.h"
#include "strl.h"
#include "stdpi.h"
#include "stdpid.h"
#include "stpid.h"
#include "ssscope.h"

# define M_PI           3.14159265358979323846  /* pi */

simModel::simModel()
{
    /* Set sim number */
    m_sim = 0;
    m_description = "PMSM abc sim Shinano";

    /* Default common params */
    m_tc = 1/20000.0;
    m_ts = m_tc/10.0;
    m_duration = 2.0;

    /* Specific params for sim */
    m_rs   = 0.6;
    m_ls   = 0.0014;
    m_flux = 0.0196;

    m_polesPairs = 2.0;
    m_inertia    = 0.000011;
    m_friction   = 0.000028;

    m_pi_iqd_bw = 6000.0;
    m_pi_iqd_kp = m_ls * m_pi_iqd_bw;
    m_pi_iqd_ki = m_rs * m_pi_iqd_bw;
    m_pi_iqd_kd = 0.0;
    m_pi_iqd_n = 0.0;

    m_pi_pos_bw =  5.0;
    m_pi_pos_kp =  m_friction * m_pi_pos_bw;
    m_pi_pos_kd =  m_inertia  * m_pi_pos_bw;
    m_pi_pos_n  =  m_pi_pos_bw * 5;
    m_pi_pos_ki =  0.0;

    /********************* *********************/
    /*      Setup parameters into the view     */
    /********************* *********************/
    m_userParams.append(new simModelElement("Electrical",   SE_group,  nullptr));
    m_userParams.append(new simModelElement("Rs",           SE_double, static_cast<void*>(&m_rs)));
    m_userParams.append(new simModelElement("Ls",           SE_double, static_cast<void*>(&m_ls)));
    m_userParams.append(new simModelElement("Flux",         SE_double, static_cast<void*>(&m_flux)));

    m_userParams.append(new simModelElement("Meccanical",   SE_group,  nullptr));
    m_userParams.append(new simModelElement("Poles Pairs",  SE_double, static_cast<void*>(&m_polesPairs)));
    m_userParams.append(new simModelElement("Inertia",      SE_double, static_cast<void*>(&m_inertia), 6));
    m_userParams.append(new simModelElement("Friction",     SE_double, static_cast<void*>(&m_friction),6));
    m_userParams.append(new simModelElement("Static brake", SE_double, static_cast<void*>(&m_staticBrake)));

    m_userParams.append(new simModelElement("Iqd Params",   SE_group,  nullptr));
    m_userParams.append(new simModelElement("IqdPIBw",      SE_double, static_cast<void*>(&m_pi_iqd_bw)));
    m_userParams.append(new simModelElement("IqdPIKp",      SE_double, static_cast<void*>(&m_pi_iqd_kp)));
    m_userParams.append(new simModelElement("IqdPIKi",      SE_double, static_cast<void*>(&m_pi_iqd_ki)));

    m_userParams.append(new simModelElement("Pos Params", SE_group,  nullptr));
    m_userParams.append(new simModelElement("PosPIBw",    SE_double, static_cast<void*>(&m_pi_pos_bw)));
    m_userParams.append(new simModelElement("PosPIKp",    SE_double, static_cast<void*>(&m_pi_pos_kp), 8));
    m_userParams.append(new simModelElement("PosPIKi",    SE_double, static_cast<void*>(&m_pi_pos_kd), 8));
    m_userParams.append(new simModelElement("PosPIn",    SE_double, static_cast<void*>(&m_pi_pos_n)));

    /********************* *********************/
}

double RadSectoRPM(double rads)
{
    return ((rads / (2.0 * M_PI)) * 60.0);
}

double RPMtoRadSec(double rpm)
{
    return ((rpm * (2.0 * M_PI)) / 60.0);
}

void simModel::startSim(void)
{
    // Test specific initialization

    // Init sim vars
    m_t = 0;
    int m_step = static_cast<int>(m_duration / m_ts);
    int m_controlStepRatio = static_cast<int>(m_tc / m_ts);

    // Init sink-source-transfer
    STPMSMabc motor(m_rs, m_ls, m_ls, m_polesPairs, m_flux, m_inertia, m_friction, m_ts, m_staticBrake, 0.001, 10 * M_PI / 180);
    STDPI idpid(m_pi_iqd_kp, m_pi_iqd_ki, m_tc, 10000);
    STDPI iqpid(m_pi_iqd_kp, m_pi_iqd_ki, m_tc, 10000);
    STDPID pospid(m_pi_pos_kp, m_pi_pos_ki, m_pi_pos_kd, m_tc * 20, 0.25);
    double posTargTeta = 2*M_PI;
    STabctodq abctodq;
    STdqtoabc dqtoabc;
    double idTarg = 0.0;
    double iqTarg = 0.0;
    SSScope iqdScope("Iqd");
    SSScope vqdScope("Vqd");
    SSScope speed("Speed rpm");
    SSScope torque("Electro magnetic Torque");
    SSScope ctorque("Cogging Torque");;
    SSScope theta("Theta");
    SSScope vabc("Vabc");
    SSScope iabc("Iabc");

    SDataVector vqin = 0 , vdin = 0;

    // Main cycle
    for (int i = 0; i < m_step; i++)
    {
        // Execution of sink and source
        double id = 0.0;
        double iq = 0.0;

        if ((i % m_controlStepRatio) == 0)
        {
            // Execution of control cycle
            SDataVector idq = abctodq.execute(SDataVector(motor.vars().Ia, motor.vars().Ib, motor.vars().ElAngle));

            id = idq.data(0, 0);
            iq = idq.data(0, 1);

            double err;
            err = idTarg - id;
            vdin = idpid.execute(err);

            err = iqTarg - iq;
            vqin = iqpid.execute(err);

            iqdScope.execute(m_t, SDataVector(iqTarg, iq, idTarg, id));
            vqdScope.execute(m_t, SDataVector(vdin, vqin));

            if ((i % (m_controlStepRatio * 20)) == 0)
            {
                // Execution of speed loop
                err = posTargTeta - motor.vars().MechAngle;
                double torqueRef = pospid.execute(err).value();
                iqTarg = torqueRef/(1.5 * m_polesPairs * m_flux);
            }

        }

        SDataVector vin = SDataVector(vdin, vqin, motor.vars().ElAngle);
        vin = dqtoabc.execute(vin);
        vabc.execute(m_t, vin);
        motor.execute(vin);
        PMSMVars iW = motor.vars();

        speed.execute(m_t, RadSectoRPM(iW.Wm));
        torque .execute(m_t, iW.T);
        ctorque.execute(m_t, iW.coggingTorque);
        theta.execute(m_t, SDataVector(iW.MechAngle));
        iabc.execute(m_t, SDataVector(iW.Ia, iW.Ib, iW.Ic));

        // Update of simutaion variables
        m_t += m_ts;

        // Update progress
        emit updateProgress(static_cast<double>(i+1)/static_cast<double>(m_step));
    }

    iqdScope.scopeUpdate();
    //vqdScope.scopeUpdate();

    torque. scopeUpdate();
    ctorque.scopeUpdate();
    speed.  scopeUpdate();

    theta.scopeUpdate();
    //vabc.scopeUpdate();
    //iabc.scopeUpdate();
}
