#include "simulationModel7.h"

#include "simulationModules/ssscope.h"
#include "simulationModules/stpid.h"
#include "simulationModules/stpmsmabc.h"
#include "simulationModules/stdqtoabc.h"
#include "simulationModules/stdqtoalphabeta.h"
#include "simulationModules/stabctodq.h"
#include "simulationModules/stsvm.h"

simulationModel7::simulationModel7()
{
    /* Set simulation number */
    m_simulation = 7;

     /* Default common params */
    m_t = 0;
    m_ts = 0.00005;
    m_tc = 0.00005;
    m_duration = 2;

    /* Specific params for simulation 8 */
    m_pi_kp = 2.90663474828051;
    m_pi_ki = 2113.6708113218;
    m_pi_kd = 0;
    m_pi_n = 0;

    m_r = 1;
    m_l = 0.001;
}

void simulationModel7::startSimulation(void)
{
    // Test specific initialization

    // Init simulation vars
    m_t = 0;
    int m_step = (int)(m_duration / m_ts);
    int m_controlStepRatio = (int)(m_tc / m_ts);

    // Init sink-source-transfer

    STPMSMabc motor(0.2, 0.0085, 0.0085, 4, 0.175, 0.089, 0.05, m_ts, 4);
    STPID idpid(m_pi_kp, m_pi_ki, m_pi_kd, m_pi_n, m_tc);
    STPID iqpid(m_pi_kp, m_pi_ki, m_pi_kd, m_pi_n, m_tc);
    STabctodq abctodq;
    STdqtoalphabeta dqtoalphabeta;
    STdqtoabc dqtoabc;
    STSVM svm;
    double idTarg = 0;
    double iqTarg = 4.76;
    SSScope sscope("Iqd",2);
    SSScope sscope2("Speed - Theta", 4);
    SSScope sscope3("Vabc SVM", 3);
    SSScope sscope3_2("Vabc SVM", 3);
    SSScope sscope4("Vabc", 3);
    SSScope sscope5("Vdq", 2);
    SSScope sscope6("Vdq svm", 2);
    SSScope sscope7("V0", 1);
    SDataVector vqin, vdin;

    // Main cycle
    for (int i = 0; i < m_step; i++)
    {
        // Execution of sink and source

        if ((i % m_controlStepRatio) == 0)
        {
            // Execution of control cycle
            double id;
            double iq;

            SDataVector idq = abctodq.execute(SDataVector(motor.vars().Ia, motor.vars().Ib, motor.vars().ElAngle));

            id = idq.data(0, 0);
            iq = idq.data(0, 1);

            double err;
            err = idTarg - id;
            vdin = idpid.execute(err);

            err = iqTarg - iq;
            vqin = iqpid.execute(err);
        }

        SDataVector vdq = SDataVector(vdin, vqin, motor.vars().ElAngle);
        sscope5.execute(m_t, SDataVector(vdin, vqin));

        SDataVector valphabeta = dqtoalphabeta.execute(vdq); // Rev Park
        SDataVector vabc = svm.execute(valphabeta);
        sscope3.execute(m_t, vabc);

        double Va = vabc.data(0, 0);
        double Vb = vabc.data(0, 1);
        double Vc = vabc.data(0, 2);
        double Vo = Va + Vb + Vc;
        double va = Va - Vo;
        double vb = Vb - Vo;
        double vc = Vc - Vo;
        sscope7.execute(m_t, Vo);
        sscope3_2.execute(m_t, SDataVector(va, vb, vc));

        SDataVector vdqsvm = abctodq.execute(SDataVector(vabc.data(0, 0) - Vo, vabc.data(0, 1) - Vo, motor.vars().ElAngle));
        sscope6.execute(m_t, vdqsvm);

        SDataVector vabc2 = dqtoabc.execute(vdq);
        sscope4.execute(m_t, vabc2);

        motor.execute(vabc2);

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
    sscope3.scopeUpdate(m_ts);
    sscope3_2.scopeUpdate(m_ts);
    sscope4.scopeUpdate(m_ts);
    sscope5.scopeUpdate(m_ts);
    sscope6.scopeUpdate(m_ts);
    sscope7.scopeUpdate(m_ts);
}

