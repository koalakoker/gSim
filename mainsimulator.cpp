#include "mainsimulator.h"
#include "simulation/sssincos.h"
#include "simulation/ssscope.h"
#include "simulation/staritmetic.h"
#include "simulation/stmux.h"
#include "simulation/stdemux.h"
#include "simulation/ssramp.h"
#include "simulation/stprev.h"
#include "simulation/strl.h"
#include "simulation/stpi.h"
#include "simulation/stdpi.h"

mainSimulator::mainSimulator()
{
    m_t = 0;
    m_ts = 0.00005;
    m_tc = 0.0001;
    m_duration = 0.01;

    m_pi_kp = 2;
    m_pi_ki = 1;
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
        o1.append(o2);
        o1.append(o3);
        o3 = smux.execute(o1);
        sscope.execute(m_t, o3);
        o2 = sdemux.execute(o3);
        sscope2.execute(m_t, o2.data(0));
        sscope3.execute(m_t, o2.data(1));
        sscope4.execute(m_t, o2.data(2));

        // Update of simutaion variables
        m_t += m_ts;
    }

    sscope.scopeUpdate(m_ts);
    sscope2.scopeUpdate(m_ts);
    sscope3.scopeUpdate(m_ts);
    sscope4.scopeUpdate(m_ts);
}

void mainSimulator::testSimulation1()
{
    // Init simulation vars
    m_t = 0;
    int m_step = (int)(m_duration / m_ts);

    // Init sink-source-transfer
    STMux smux;
    SSRamp sramp(2,0.1);
    SSSinCos ssin(10);
    SSSinCos ssin2(1);
    SSSinCos ssin3(1);
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
    }

    sscope.scopeUpdate(m_ts);
}

void mainSimulator::testSimulation2()
{
    // Init simulation vars
    m_t = 0;
    int m_step = (int)(m_duration / m_ts);

    // Init sink-source-transfer
    STMux smux;
    SSSinCos ssin(10);
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
    }

    sscope.scopeUpdate(m_ts);
}

void mainSimulator::testSimulation3()
{
    // Init simulation vars
    m_t = 0;
    int m_step = (int)(m_duration / m_ts);
    int m_controlStepRatio = (int)(m_tc / m_ts);

    // Init sink-source-transfer
    SSScope sscope("Current");
    SSScope sscope2("Voltage");
    SSScope sscope3("Error");
    STRL strl(1, 0.001, m_ts);
    STDPI stpi(m_pi_kp, m_pi_ki);
    double iprev = 0;
    double iTarg = 10;
    SDataVector vin;

    // Main cycle
    for (int i = 0; i < m_step; i++)
    {
        // Execution of sink and source

        if ((i % m_controlStepRatio) == 0)
        {
            // Execution of control cycle
            double err;
            err = iTarg - iprev;
            SDataVector errDV;
            errDV.setValue(err);
            sscope3.execute(m_t, errDV);
            vin = stpi.execute(errDV);
            sscope2.execute(m_t, vin);
        }

        SDataVector iRL = strl.execute(vin);
        sscope.execute(m_t, iRL);
        iprev = iRL.value();

        // Update of simutaion variables
        m_t += m_ts;
    }

    sscope.scopeUpdate(m_ts);
    //sscope2.scopeUpdate(m_ts);
    //sscope3.scopeUpdate(m_ts);
}
