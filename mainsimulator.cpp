#include "mainsimulator.h"

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

    // Init sink-source
    SSSin ssin;
    ssin.setAmplitude(1);
    ssin.setFrequency(1);
    SSScope sscope;

    // Main cycle
    for (int i = 0; i < step; i++)
    {
        // Execution of sink and source
        sscope.execute(t, ssin.execute(t));

        // Update of simutaion variables
        t += dt;
    }

    sscope.scopeUpdate(dt);
}
