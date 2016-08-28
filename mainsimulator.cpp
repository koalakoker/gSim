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
#include "simulation/stpid.h"
#include "simulation/stpmsmdq.h"
#include "simulation/stpmsmabc.h"
#include "simulation/stfintegrator.h"
#include "simulation/stdqtoabc.h"
#include "simulation/stabctodq.h"

mainSimulator::mainSimulator()
{
    m_t = 0;
    m_ts = 0.00005;
    m_tc = 0.00005;
    m_duration = 2;

    m_pi_kp = 2.90663474828051;
    m_pi_ki = 2113.6708113218;
    m_pi_kd = 0;
    m_pi_n = 0;

    m_r = 1;
    m_l = 0.001;

    m_simulation = 6;
}

void mainSimulator::startSimulation(void)
{
    int simulation = m_simulation;

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
    case 4:
        testSimulation4();
        break;
    case 5:
        testSimulation5();
        break;
    case 6:
        testSimulation6();
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
        o3 = smux.execute(SDataVector(o1, o2, o3));
        sscope.execute(m_t, o3);
//        o2 = sdemux.execute(o3);
//        sscope2.execute(m_t, o2.data(0));
//        sscope3.execute(m_t, o2.data(1));
//        sscope4.execute(m_t, o2.data(2));

        // Update of simutaion variables
        m_t += m_ts;
    }

    sscope.scopeUpdate(m_ts);
//    sscope2.scopeUpdate(m_ts);
//    sscope3.scopeUpdate(m_ts);
//    sscope4.scopeUpdate(m_ts);
}

void mainSimulator::testSimulation1()
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
    }

    sscope.scopeUpdate(m_ts);
}

void mainSimulator::testSimulation3()
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

    // Init simulation vars
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
    }

    sscope.scopeUpdate(m_ts);
    //sscope2.scopeUpdate(m_ts);
    //sscope3.scopeUpdate(m_ts);
    sscope4.scopeUpdate(m_ts);
    //sscope5.scopeUpdate(m_ts);
}

void mainSimulator::testSimulation4()
{
    // Test specific initialization
    m_ts = 0.00005;
    m_tc = 0.0001;
    m_duration = 0.01;

    m_pi_kp = 2.90663474828051;
    m_pi_ki = 2113.6708113218;
    m_pi_kd = 0.000111756425508289;
    m_pi_n = 2514.9905893422;

    m_r = 1;
    m_l = 0.001;

    // Init simulation vars
    m_t = 0;
    int m_step = (int)(m_duration / m_ts);
    int m_controlStepRatio = (int)(m_tc / m_ts);

    // Init sink-source-transfer
    SSScope sscope("Current PID - Forward Euler");
    SSScope sscope2("Current PID - Backward Euler");
    SSScope sscope3("Current PID - Trapezoidal");
    STRL strl(m_r, m_l, m_ts);
    STRL strl2(m_r, m_l, m_ts);
    STRL strl3(m_r, m_l, m_ts);
    STPID stpid(m_pi_kp, m_pi_ki, m_pi_kd, m_pi_n, m_tc, ForwardEuler);
    STPID stpid2(m_pi_kp, m_pi_ki, m_pi_kd, m_pi_n, m_tc, BackwardEuler);
    STPID stpid3(m_pi_kp, m_pi_ki, m_pi_kd, m_pi_n, m_tc, Trapezoidal);
    double iprev = 0;
    double iprev2 = 0;
    double iprev3 = 0;
    double iTarg = 10;
    SDataVector vin, vin2, vin3;

    // Main cycle
    for (int i = 0; i < m_step; i++)
    {
        // Execution of sink and source

        if ((i % m_controlStepRatio) == 0)
        {
            // Execution of control cycle
            double err;
            err = iTarg - iprev;
            vin = stpid.execute(err);

            err = iTarg - iprev2;
            vin2 = stpid2.execute(err);

            err = iTarg - iprev3;
            vin3 = stpid3.execute(err);

        }

        SDataVector iRL = strl.execute(vin);
        sscope.execute(m_t, iRL);
        iprev = iRL.value();

        iRL = strl2.execute(vin2);
        sscope2.execute(m_t, iRL);
        iprev2 = iRL.value();

        iRL = strl3.execute(vin3);
        sscope3.execute(m_t, iRL);
        iprev3 = iRL.value();

        // Update of simutaion variables
        m_t += m_ts;
    }

    sscope.scopeUpdate(m_ts);
    sscope2.scopeUpdate(m_ts);
    sscope3.scopeUpdate(m_ts);
}

void mainSimulator::testSimulation5()
{
    // Test specific initialization

    // Init simulation vars
    m_t = 0;
    int m_step = (int)(m_duration / m_ts);
    int m_controlStepRatio = (int)(m_tc / m_ts);

    // Init sink-source-transfer

    STPMSMdq motor(0.2, 0.0085, 0.0085, 4, 0.175, 0.089, 0.05, m_ts, 4);
    STPID idpid(m_pi_kp, m_pi_ki, m_pi_kd, m_pi_n, m_tc);
    STPID iqpid(m_pi_kp, m_pi_ki, m_pi_kd, m_pi_n, m_tc);
    double iqTarg = 4.76;
    double idTarg = 0;
    SDataVector vqin, vdin;
    SSScope sscope("Iqd",2);
    SSScope sscope2("Speed - Theta", 4);

    // Main cycle
    for (int i = 0; i < m_step; i++)
    {
        // Execution of sink and source

        if ((i % m_controlStepRatio) == 0)
        {
            // Execution of control cycle
            double err;
            err = idTarg - motor.vars().Id;
            vdin = idpid.execute(err);

            err = iqTarg - motor.vars().Iq;
            vqin = iqpid.execute(err);
        }

        SDataVector vin = SDataVector(vdin, vqin);
        PMSMVars iW = motor.execute(vin);
        sscope.execute(m_t, SDataVector(iW.Iq,iW.Id));
        sscope2.execute(m_t, SDataVector(iW.Wm, iW.MechAngle, iW.We, iW.ElAngle));

        // Update of simutaion variables
        m_t += m_ts;
    }

    sscope.scopeUpdate(m_ts);
    sscope2.scopeUpdate(m_ts);
}

void mainSimulator::testSimulation6()
{
    // Test specific initialization

    // Init simulation vars
    m_t = 0;
    int m_step = (int)(m_duration / m_ts);
    int m_controlStepRatio = (int)(m_tc / m_ts);

    // Init sink-source-transfer

    STPMSMabc motor(0.2, 0.0085, 0.0085, 4, 0.175, 0.089, 0.05, m_ts, 4);
    STPID idpid(m_pi_kp, m_pi_ki, m_pi_kd, m_pi_n, m_tc);
    STPID iqpid(m_pi_kp, m_pi_ki, m_pi_kd, m_pi_n, m_tc);
    STabctodq abctodq;
    STdqtoabc dqtoabc;
    double idTarg = 0;
    double iqTarg = 4.76;
    SSScope sscope("Iqd",2);
    SSScope sscope2("Speed - Theta", 4);
    SDataVector vqin, vdin;

    // Main cycle
    for (int i = 0; i < m_step; i++)
    {
        // Execution of sink and source

        if ((i % m_controlStepRatio) == 0)
        {
            // Execution of control cycle
            double id;
            double iq;

            SDataVector idq = abctodq.execute(SDataVector(motor.vars().Ia, motor.vars().Ib, motor.vars().ElAngle));

            id = idq.data(0, 0);
            iq = idq.data(0, 1);

            double err;
            err = idTarg - id;
            vdin = idpid.execute(err);

            err = iqTarg - iq;
            vqin = iqpid.execute(err);
        }

        SDataVector vin = SDataVector(vdin, vqin, motor.vars().ElAngle);
        vin = dqtoabc.execute(vin);

        PMSMVars iW = motor.execute(vin);
        sscope.execute(m_t, SDataVector(iW.Iq,iW.Id));
        sscope2.execute(m_t, SDataVector(iW.Wm, iW.MechAngle, iW.We, iW.ElAngle));

        // Update of simutaion variables
        m_t += m_ts;

        // Update progress
        emit updateProgress((double)(i+1)/(double)m_step);
    }

    sscope.scopeUpdate(m_ts);
    sscope2.scopeUpdate(m_ts);
}
