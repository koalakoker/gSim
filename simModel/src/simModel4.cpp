#include "simModel.h"

#include "ssscope.h"
#include "strl.h"
#include "stpid.h"

simModel::simModel()
{
    /* Set sim number */
    m_sim = 4;
    m_description = "PI (different types) on RL sim";
}


void simModel::startSim(void)
{
    // Test specific initialization
    m_ts = 0.00005;
    m_tc = 0.0001;
    m_duration = 0.01;

    m_pi_kp = 2.90663474828051;
    m_pi_ki = 2113.6708113218;
    m_pi_kd = 0.000111756425508289;
    m_pi_n = 2514.9905893422;

    m_r = 1;
    m_l = 0.001;

    // Init sim vars
    m_t = 0;
    int m_step = (int)(m_duration / m_ts);
    int m_controlStepRatio = (int)(m_tc / m_ts);

    // Init sink-source-transfer
    SSScope sscope("Current PID - Forward Euler");
    SSScope sscope2("Current PID - Backward Euler");
    SSScope sscope3("Current PID - Trapezoidal");
    STRL strl(m_r, m_l, m_ts);
    STRL strl2(m_r, m_l, m_ts);
    STRL strl3(m_r, m_l, m_ts);
    STPID stpid(m_pi_kp, m_pi_ki, m_pi_kd, m_pi_n, m_tc, ForwardEuler);
    STPID stpid2(m_pi_kp, m_pi_ki, m_pi_kd, m_pi_n, m_tc, BackwardEuler);
    STPID stpid3(m_pi_kp, m_pi_ki, m_pi_kd, m_pi_n, m_tc, Trapezoidal);
    double iprev = 0;
    double iprev2 = 0;
    double iprev3 = 0;
    double iTarg = 10;
    SDataVector vin, vin2, vin3;

    // Main cycle
    for (int i = 0; i < m_step; i++)
    {
        // Execution of sink and source

        if ((i % m_controlStepRatio) == 0)
        {
            // Execution of control cycle
            double err;
            err = iTarg - iprev;
            vin = stpid.execute(err);

            err = iTarg - iprev2;
            vin2 = stpid2.execute(err);

            err = iTarg - iprev3;
            vin3 = stpid3.execute(err);

        }

        SDataVector iRL = strl.execute(vin);
        sscope.execute(m_t, iRL);
        iprev = iRL.value();

        iRL = strl2.execute(vin2);
        sscope2.execute(m_t, iRL);
        iprev2 = iRL.value();

        iRL = strl3.execute(vin3);
        sscope3.execute(m_t, iRL);
        iprev3 = iRL.value();

        // Update of simutaion variables
        m_t += m_ts;

        // Update progress
        emit updateProgress((double)(i+1)/(double)m_step);
    }

    sscope.scopeUpdate(m_ts);
    sscope2.scopeUpdate(m_ts);
    sscope3.scopeUpdate(m_ts);
}
