#include "simulationModel0.h"

#include "simulationModules/sssincos.h"
#include "simulationModules/ssscope.h"
#include "simulationModules/staritmetic.h"
#include "simulationModules/stmux.h"
#include "simulationModules/stdemux.h"

simulationModel0::simulationModel0()
{
    /* Set simulation number */
    m_simulation = 0;

    /* Default common params */
    m_t = 0;
    m_ts = 0.00005;
    m_tc = 0.00005;
    m_duration = 2;
}

void simulationModel0::startSimulation(void)
{
    // Init simulation vars
    m_t = 0;
    int m_step = (int)(m_duration / m_ts);

    // Init sink-source-transfer
    SSSinCos ssin;
    SSSinCos scos(SSSinCos::cosType);
    SSScope sscope("Mux", 3);
    SSScope sscope2("Demux 1");
    SSScope sscope3("Demux 2");
    SSScope sscope4("Demux 3");
    STAritmetic ssum(STAritmetic::sumType);
    STMux smux;
    STDemux sdemux;

    // Main cycle
    for (int i = 0; i < m_step; i++)
    {
        // Execution of sink and source
        SDataVector o1 = ssin.execute(m_t);
        SDataVector o2 = scos.execute(m_t);
        SDataVector o3 = ssum.execute(o1, o2);

        o3 = sdemux.execute(SDataVector(o1, o2, o3));
        sscope2.execute(m_t, o3.data(0));
        sscope3.execute(m_t, o3.data(1));
        sscope4.execute(m_t, o3.data(2));

        o3 = smux.execute(o3);
        sscope.execute(m_t, o3);

        // Update of simutaion variables
        m_t += m_ts;

        // Update progress
        emit updateProgress((double)(i+1)/(double)m_step);
    }

    sscope.scopeUpdate(m_ts);
    sscope2.scopeUpdate(m_ts);
    sscope3.scopeUpdate(m_ts);
    sscope4.scopeUpdate(m_ts);
}
