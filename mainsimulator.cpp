#include "mainsimulator.h"
#include "simulation/sssincos.h"
#include "simulation/ssscope.h"
#include "simulation/staritmetic.h"
#include "simulation/stmux.h"
#include "simulation/stdemux.h"
#include "simulation/ssramp.h"
#include "simulation/stprev.h"
#include "simulation/strl.h"

mainSimulator::mainSimulator()
{
    t = 0;
    dt = 0.001;
    duration = 1;
}

void mainSimulator::startSimulation(void)
{
    int simulation = 3;

    switch (simulation) {
    case 0:
        testSimulation0();
        break;
    case 1:
        testSimulation1();
        break;
    case 2:
        testSimulation2();
        break;
    case 3:
        testSimulation3();
        break;
    default:
        break;
    }
}

void mainSimulator::testSimulation0()
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

void mainSimulator::testSimulation1()
{
    // Init simulation vars
    t = 0;
    step = (int)(duration / dt);

    // Init sink-source-transfer
    STMux smux;
    SSRamp sramp(2,0.1);
    SSSinCos ssin(10);
    SSSinCos ssin2(1);
    SSSinCos ssin3(1);
    SSScope sscope("Ramp - Ramp Ampl - Ramp Freq - Ramp AmplFreq ", 4);

    // Main cycle
    for (int i = 0; i < step; i++)
    {
        // Execution of sink and source
        SDataVector o1 = sramp.execute(t);

        ssin.setAmplitude(o1.data(0,0));
        ssin2.setFrequency(o1.data(0,0) * 10);
        ssin3.setAmplitude(ssin.amplitude());
        ssin3.setFrequency(ssin2.frequency());
        o1.append(ssin.execute(t));
        o1.append(ssin2.execute(t));
        o1.append(ssin3.execute(t));

        o1 = smux.execute(o1);

        sscope.execute(t, o1);

        // Update of simutaion variables
        t += dt;
    }

    sscope.scopeUpdate(dt);
}

void mainSimulator::testSimulation2()
{
    // Init simulation vars
    t = 0;
    step = (int)(duration / dt);

    // Init sink-source-transfer
    STMux smux;
    SSSinCos ssin(10);
    SSScope sscope("Prev");
    STPrev sprev;
    STAritmetic sdiff(STAritmetic::differenceType);

    // Main cycle
    for (int i = 0; i < step; i++)
    {
        // Execution of sink and source
        SDataVector o1 = ssin.execute(t);
        SDataVector o2 = sprev.execute(o1);
        SDataVector o3 = sdiff.execute(o2, o1);

        sscope.execute(t, o3);

        // Update of simutaion variables
        t += dt;
    }

    sscope.scopeUpdate(dt);
}

void mainSimulator::testSimulation3()
{
    // Init simulation vars
    t = 0;
    step = (int)(duration / dt);

    // Init sink-source-transfer
    SSScope sscope("I");
    STRL strl(1, 0.001, dt);
    SDataVector vin;
    vin.setValue(1); // 1V Constant

    // Main cycle
    for (int i = 0; i < step; i++)
    {
        // Execution of sink and source
        SDataVector o1 = strl.execute(vin);

        sscope.execute(t, o1);

        // Update of simutaion variables
        t += dt;
    }

    sscope.scopeUpdate(dt);
}
