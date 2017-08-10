#include "simModel9.h"

#include "simModules/stpmsmdq.h"
#include "simModules/stpid.h"
#include "simModules/ssscope.h"

simModel9::simModel9()
{
    /* Set sim number */
    m_sim = 9;
    m_description = "Motor mechanical sim";

    /* Default common params */
    m_ts = 0.00005;
    m_tc = 0.00005;
    m_duration = 2;

    /* Specific params for sim 9 */
    m_pi_kp = 2.90663474828051;
    m_pi_ki = 2113.6708113218;
    m_pi_kd = 0;
    m_pi_n = 0;

    m_r = 1;
    m_l = 0.001;
}

void simModel9::startSim(void)
{
    // Test specific initialization

    // Init sim vars
    m_t = 0;
    int m_step = (int)(m_duration / m_ts);
    int m_controlStepRatio = (int)(m_tc / m_ts);

    // Init sink-source-transfer

    STPMSMdq motor(0.2, 0.0085, 0.0085, 4, 0.175, 0.089, 0.05, m_ts, 4);
    STPID idpid(m_pi_kp, m_pi_ki, m_pi_kd, m_pi_n, m_tc);
    STPID iqpid(m_pi_kp, m_pi_ki, m_pi_kd, m_pi_n, m_tc);
    double iqTarg = 4.76;
    double idTarg = 0;
    SDataVector vqin, vdin;
    SSScope sscope("Iqd",2);
    SSScope sscope2("Speed - Theta", 4);

    // Main cycle
    for (int i = 0; i < m_step; i++)
    {
        // Execution of sink and source

        if ((i % m_controlStepRatio) == 0)
        {
            // Execution of control cycle
            double err;
            err = idTarg - motor.vars().Id;
            vdin = idpid.execute(err);

            err = iqTarg - motor.vars().Iq;
            vqin = iqpid.execute(err);
        }

        SDataVector vin = SDataVector(vdin, vqin);
        motor.execute(vin);
        PMSMVars iW = motor.vars();
        sscope.execute(m_t, SDataVector(iW.Iq,iW.Id));
        sscope2.execute(m_t, SDataVector(iW.Wm, iW.MechAngle, iW.We, iW.ElAngle));

        // Update of simutaion variables
        m_t += m_ts;

        // Update progress
        emit updateProgress((double)(i+1)/(double)m_step);
    }

    sscope.scopeUpdate(m_ts);
    sscope2.scopeUpdate(m_ts);
}
