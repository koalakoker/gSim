#include "simulationModel8.h"
#include "simulationModules/ssscope.h"

simulationModel8::simulationModel8()
{
    /* Set simulation number */
    m_simulation = 8;
    m_description = "Resolver simulation";

    /* Default common params */
    m_t = 0;
    m_ts = 0.00005;
    m_tc = 0.00005;
    m_duration = 0.02;

    /* Specific params for simulation 8 */
    m_exc_freq = 1000;
    m_exc_ampl = 15;
    m_motSpeedRads = 400;
    m_sin_att = 0.8;
    m_sin_delay = 0.0;
    m_sin_offset = 0.0;
    m_cos_att = 0.8;
    m_cos_delay = 0.0;
    m_cos_offset = 0.0;

    /* Plots */
    excitingPlot = false;
    outputsPlot = true;
    thetaPlot = false;
}

void simulationModel8::startSimulation(void)
{
    // Test specific initialization
    double theta = 0;

    // Init simulation vars
    m_t = 0;
    int m_step = (int)(m_duration / m_ts);

    // Init sink-source-transfer
    SSScope sscope("Exciting signal",1);
    SSScope sscope2("Output signals",2);
    SSScope sscope3("Theta",1);

    // Main cycle
    for (int i = 0; i < m_step; i++)
    {
        // Execution of sink and source
        theta = m_t * m_motSpeedRads;
        double exc_sinwt = m_exc_ampl * sin(2 * M_PI * m_exc_freq * m_t);
        double sin_sinwt = m_exc_ampl * sin(2 * M_PI * m_exc_freq * m_t + m_sin_delay);
        double cos_sinwt = m_exc_ampl * sin(2 * M_PI * m_exc_freq * m_t + m_cos_delay);
        double sinTheta = sin(theta);
        double cosTheta = cos(theta);
        double secondarySin = (m_sin_att * sin_sinwt * sinTheta) + m_sin_offset;
        double secondaryCos = (m_cos_att * cos_sinwt * cosTheta) + m_cos_offset;

        if (excitingPlot)
        {
            sscope.execute(m_t, SDataVector(exc_sinwt));
        }
        if (outputsPlot)
        {
            sscope2.execute(m_t, SDataVector(secondarySin, secondaryCos));
        }
        if (thetaPlot)
        {
            sscope3.execute(m_t, SDataVector(theta));
        }

        // Update of simutaion variables
        m_t += m_ts;

        // Update progress
        emit updateProgress((double)(i+1)/(double)m_step);
    }

    if (excitingPlot)
    {
        sscope.scopeUpdate(m_ts);
    }
    if (outputsPlot)
    {
        sscope2.scopeUpdate(m_ts);
    }
    if (thetaPlot)
    {
        sscope3.scopeUpdate(m_ts);
    }
}

