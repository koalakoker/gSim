#include "simModel2.h"

#include "simModules/stmux.h"
#include "simModules/sssincos.h"
#include "simModules/ssscope.h"
#include "simModules/stprev.h"
#include "simModules/staritmetic.h"

simModel2::simModel2()
{
    /* Set sim number */
    m_sim = 2;
    m_description = "Previous value sim";
}

void simModel2::startSim(void)
{
    // Init sim vars
    m_t = 0;
    int m_step = (int)(m_duration / m_ts);

    // Init sink-source-transfer
    STMux smux;
    SSSinCos ssin(SSSinCos::sinType, 10);
    SSScope sscope("Prev");
    STPrev sprev;
    STAritmetic sdiff(STAritmetic::differenceType);

    // Main cycle
    for (int i = 0; i < m_step; i++)
    {
        // Execution of sink and source
        SDataVector o1 = ssin.execute(m_t);
        SDataVector o2 = sprev.execute(o1);
        SDataVector o3 = sdiff.execute(o2, o1);

        sscope.execute(m_t, o3);

        // Update of simutaion variables
        m_t += m_ts;

        // Update progress
        emit updateProgress((double)(i+1)/(double)m_step);
    }

    sscope.scopeUpdate(m_ts);
}
