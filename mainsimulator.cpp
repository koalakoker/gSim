#include "mainsimulator.h"
#include "simulation/sssincos.h"
#include "simulation/ssscope.h"
#include "simulation/staritmetic.h"

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
    SSScope sscope("Sin");
    SSScope sscope2("Cos");
    STAritmetic ssum(STAritmetic::sumType);

    // Main cycle
    for (int i = 0; i < step; i++)
    {
        // Execution of sink and source
        SDataVector o1 = ssin.execute(t);
        SDataVector o2 = scos.execute(t);
        SDataVector o3 = ssum.execute(o1, o2);
        sscope.execute(t, o3);
        sscope2.execute(t, o2);

        // Update of simutaion variables
        t += dt;
    }

    sscope.scopeUpdate(dt);
    sscope2.scopeUpdate(dt);
}
