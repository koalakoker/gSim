#include "simulationModel1.h"

#include "simulationModules/stmux.h"
#include "simulationModules/sssincos.h"
#include "simulationModules/ssscope.h"
#include "simulationModules/ssramp.h"

simulationModel1::simulationModel1()
{
    /* Set simulation number */
    m_simulation = 1;
    m_description = "Sin variable-ramp  simulation";
}

void simulationModel1::startSimulation(void)
{
    // Init simulation vars
    m_t = 0;
    int m_step = (int)(m_duration / m_ts);

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
