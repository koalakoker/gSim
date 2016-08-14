#include "mainsimulator.h"
#include "simulation/sssincos.h"
#include "simulation/ssscope.h"
#include "simulation/staritmetic.h"
#include "simulation/stmux.h"
#include "simulation/stdemux.h"

mainSimulator::mainSimulator()
{
    t = 0;
    dt = 0.001;
    duration = 1;
}

void mainSimulator::startSimulation(void)
{
    // Init simulation vars
    t = 0;
    step = (int)(duration / dt);

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
    for (int i = 0; i < step; i++)
    {
        // Execution of sink and source
        SDataVector o1 = ssin.execute(t);
        SDataVector o2 = scos.execute(t);
        SDataVector o3 = ssum.execute(o1, o2);
        o1.append(o2);
        o1.append(o3);
        o3 = smux.execute(o1);
        sscope.execute(t, o3);
        o2 = sdemux.execute(o3);
        sscope2.execute(t, o2.data(0));
        sscope3.execute(t, o2.data(1));
        sscope4.execute(t, o2.data(2));

        // Update of simutaion variables
        t += dt;
    }

    sscope.scopeUpdate(dt);
    sscope2.scopeUpdate(dt);
    sscope3.scopeUpdate(dt);
    sscope4.scopeUpdate(dt);
}
