#include "simModel.h"

#include "stmux.h"
#include "sssincos.h"
#include "ssscope.h"
#include "ssramp.h"

simModel::simModel()
{
    /* Set sim number */
    m_sim = 1;
    m_description = "Sin variable-ramp  sim";

    /* Default common params */
    m_ts = 0.00005;
    m_tc = 0.00005;
    m_duration = 2;
}

void simModel::startSim(void)
{
    // Init sim vars
    m_t = 0;
    int m_step = (int)(m_duration / m_ts);
    /********************* *********************/
    /* Define here the behaviour of your model */
    /********************* *********************/

    // Init sink-source-transfer
    STMux smux;
    SSRamp sramp(2,0.1);
    SSSinCos ssin(SSSinCos::sinType, 10);
    SSSinCos ssin2(SSSinCos::sinType, 1);
    SSSinCos ssin3(SSSinCos::sinType, 1);
    SSScope sscope("Ramp - Ramp Ampl - Ramp Freq - Ramp AmplFreq ", 4);

    // Main cycle
    for (int i = 0; i < m_step; i++)
    {
        // Execution of sink and source
        SDataVector o1 = sramp.execute(m_t);

        ssin.setAmplitude(o1.data(0,0));
        ssin2.setFrequency(o1.data(0,0) * 10);
        ssin3.setAmplitude(ssin.amplitude());
        ssin3.setFrequency(ssin2.frequency());
        o1.append(ssin.execute(m_t));
        o1.append(ssin2.execute(m_t));
        o1.append(ssin3.execute(m_t));

        o1 = smux.execute(o1);

        sscope.execute(m_t, o1);

        // Update of simutaion variables
        m_t += m_ts;

        // Update progress
        emit updateProgress((double)(i+1)/(double)m_step);
    }

    sscope.scopeUpdate(m_ts);
}
