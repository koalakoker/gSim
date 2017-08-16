#include "simModel.h"

#include "ssscope.h"
#include "strl.h"
#include "stpi.h"
#include "stdpi.h"
#include "staritmetic.h"

simModel::simModel()
{
    /* Set sim number */
    m_sim = 3;
    m_description = "PI on RL sim";

    /* Default common params */
    m_ts = 0.00005;
    m_tc = 0.00005;
    m_duration = 2;
}

void simModel::startSim(void)
{
    // Test specific initialization
    m_ts = 0.00005;
    m_tc = 0.0001;
    m_duration = 0.01;

    m_pi_kp = 1.21;
    m_pi_ki = 1040;
    m_pi_kd = 0;
    m_pi_n = 0;

    m_r = 1;
    m_l = 0.001;

    // Init sim vars
    m_t = 0;
    int m_step = (int)(m_duration / m_ts);
    int m_controlStepRatio = (int)(m_tc / m_ts);

    // Init sink-source-transfer
    SSScope sscope("Current DPI");
    SSScope sscope2("Voltage");
    SSScope sscope3("Error");
    SSScope sscope4("Current PI");
    SSScope sscope5("Difference");
    STRL strl(m_r, m_l, m_ts);
    STRL strl2(m_r, m_l, m_ts);
    STDPI stdpi(m_pi_kp, m_pi_ki * m_tc);
    STPI stpi(m_pi_kp, m_pi_ki, m_tc);
    double iprev = 0;
    double iprev2 = 0;
    double iTarg = 10;
    SDataVector vin,vin2;

    // Main cycle
    for (int i = 0; i < m_step; i++)
    {
        // Execution of sink and source

        if ((i % m_controlStepRatio) == 0)
        {
            // Execution of control cycle
            double err;
            err = iTarg - iprev;
            sscope3.execute(m_t, err);
            vin = stdpi.execute(err);
            sscope2.execute(m_t, vin);

            err = iTarg - iprev2;
            vin2 = stpi.execute(err);
        }

        SDataVector iRL = strl.execute(vin);
        SDataVector iRL2 = strl2.execute(vin2);
        sscope.execute(m_t, iRL);
        sscope4.execute(m_t, iRL2);
        sscope5.execute(m_t, STAritmetic(STAritmetic::differenceType).execute(iRL,iRL2));
        iprev = iRL.value();
        iprev2 = iRL2.value();

        // Update of simutaion variables
        m_t += m_ts;

        // Update progress
        emit updateProgress((double)(i+1)/(double)m_step);
    }

    sscope.scopeUpdate(m_ts);
    //sscope2.scopeUpdate(m_ts);
    //sscope3.scopeUpdate(m_ts);
    sscope4.scopeUpdate(m_ts);
    //sscope5.scopeUpdate(m_ts);
}
