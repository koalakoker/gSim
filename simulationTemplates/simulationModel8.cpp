#include "simulationModel8.h"
#include "simulationModules/ssscope.h"
#include "simulationModules/stfintegrator.h"
#include "simulationModules/stpid.h"
#include "simulationModules/stmotormech.h"
#include "simulationModules/stdelay.h"

simulationModel8::simulationModel8()
{
    /* Set simulation number */
    m_simulation = 8;
    m_description = "Resolver simulation";

    /* Default common params */
    m_t = 0;
    m_ts = 0.00000625;
    m_duration = 4.0;

    /* Specific params for simulation 8 */
    m_exc_freq = 4000;
    m_tc = 1/m_exc_freq;
    m_exc_ampl = 15;
    m_sin_att = 0.8;
    m_sin_delay = 0.0;
    m_sin_offset = 0.0;
    m_cos_att = 0.8;
    m_cos_delay = 0.0;
    m_cos_offset = 0.0;

    /* Motor deafult values */
    m_polesPairs = 4.0;
    m_inertia = 0.0010;
    m_friction = 0.0050;
    m_torque = 1.0;

    /* Plots */
    m_excitingPlot = false;
    m_outputsPlot = false;
    m_demuxOutputsPlot = false;
    m_thetaPlot = true;
    m_omegaPlot = true;
    m_deltaAngle = true;

    //
    PI_KP = 200.0;
    PI_KI = 10000.0000;
}

void simulationModel8::startSimulation(void)
{
    // Test specific initialization
    double theta = 0;

    // Init simulation vars
    m_t = 0;
    int m_step = (int)(m_duration / m_ts);

    m_resSinDem = 0;
    m_resCosDem = 0;
    k = 0;

    // Init sink-source-transfer
    SSScope sscope("Exciting signal",1);
    SSScope sscope2("Sin/Cos signals",2);
    SSScope sscope5("Sin/Cos demodulated signals",2);
    SSScope sscope3("Mechanical angle: real (black) tracked (blue)",2);
    SSScope sscope4("Mechanical speed: real (black) tracked (blue)",2);
    SSScope sscope8("Delta angle",1);

    STPID stpid(PI_KP, PI_KI, 0, 0, m_tc, BackwardEuler);
    STFIntegrator stfInt(m_tc, Trapezoidal);
    resolverInit();
    STMotorMech motor(m_polesPairs, m_inertia, m_friction, m_ts, false);

    STDelay delaySin(m_ts,m_sin_delay);
    STDelay delayCos(m_ts,m_cos_delay);

    // Main cycle
    for (int i = 0; i < m_step; i++)
    {
        // Execution of sink and source

        /* Motor update */

        /* Execute two torque steps */
        if (m_t < 2.0)
        {
            m_torque = 1.0;
        }
        else
        {
            m_torque = -1.0;
        }
        motor.execute(m_torque);
        MotorMechVars iW = motor.vars();

        /* Execute resolver update */
        theta = iW.MechAngle;
        double exc_sinwt = m_exc_ampl * sin(2 * M_PI * m_exc_freq * m_t);

        //double sin_sinwt = m_exc_ampl * sin(2 * M_PI * m_exc_freq * m_t + m_sin_delay);
        double ds = delaySin.execute(exc_sinwt).value();
        //double cos_sinwt = m_exc_ampl * sin(2 * M_PI * m_exc_freq * m_t + m_cos_delay);
        double dc = delayCos.execute(exc_sinwt).value();

        double sinTheta = sin(theta);
        double cosTheta = cos(theta);
        double secondarySin = (m_sin_att * ds * sinTheta) + m_sin_offset;
        double secondaryCos = (m_cos_att * dc * cosTheta) + m_cos_offset;

        if (m_excitingPlot)
        {
            sscope.execute(m_t, SDataVector(exc_sinwt));
        }

        if (m_outputsPlot)
        {
            sscope2.execute(m_t, SDataVector(secondarySin, secondaryCos));
        }

        double tc = (0.25 + k) * m_tc; /* tc = (1/4 + k) * DThf */
        if ((m_t <= tc) && (tc < (m_t + m_ts)))
        {
            // Sampling inputs sin/cos demodulated
            m_resSinDem = secondarySin;
            m_resCosDem = secondaryCos;
            k++;

            if (m_demuxOutputsPlot)
            {
                sscope5.execute(m_t, SDataVector(m_resSinDem, m_resCosDem));
            }

            if (m_thetaPlot)
            {
                sscope3.execute(m_t, SDataVector(theta, phi));
            }

            /* Resolver decoding */
            double s = m_resSinDem * cos(phi); /* Vs * cos(phi) */
            double c = m_resCosDem * sin(phi); /* Vc * sen(phi) */
            double d = s - c; /* (Vs * cos(phi)) - (Vc * sen(phi)) */

            omega = stpid.execute(d).value(); /* mf is the error at the imput of the PI (teta - phi) */ /* The output is the tracked angular speed of the motor */

            if (m_deltaAngle)
            {
                sscope8.execute(m_t, SDataVector(theta - phi));
            }

            phi = stfInt.execute(omega).value(); /* Integrator to get the tracked angle */

            if (m_omegaPlot)
            {
                sscope4.execute(m_t, SDataVector(iW.Wm, omega));
            }
        }

        // Update of simutaion variables
        m_t += m_ts;

        // Update progress
        emit updateProgress((double)(i+1)/(double)m_step);
    }

    if (m_excitingPlot)
    {
        sscope.scopeUpdate(m_ts);
    }
    if (m_outputsPlot)
    {
        sscope2.scopeUpdate(m_ts);
    }
    if (m_thetaPlot)
    {
        sscope3.scopeUpdate(m_ts);
    }
    if (m_omegaPlot)
    {
        sscope4.scopeUpdate(m_ts);
    }
    if (m_demuxOutputsPlot)
    {
        sscope5.scopeUpdate(m_ts);
    }
    if (m_deltaAngle)
    {
        sscope8.scopeUpdate(m_ts);
    }
}

void simulationModel8::resolverInit(void)
{
    phi = 0;
    omega = 0;
}

void simulationModel8::resolverExec(void)
{

}
