#include "simModel.h"

#include "stfintegrator.h"
#include "plot\ssscope.h"
#include "math.h"

# define M_PI           3.14159265358979323846  /* pi */

simModel::simModel()
{
    /* Set sim number */
    m_sim = 0;
    m_description = "Second order system";

    /* Default common params */
    m_duration = 0.0003;
    m_ts = m_duration / 100;

    /* Specific params for sim */
    m_naturalfreq = 25000; // rad/s
    m_damping = 0.7;
    m_targ = 1;

    /********************* *********************/
    /*      Setup parameters into the view     */
    /********************* *********************/
    m_userParams.append(new simModelElement("Params",            SE_group,  nullptr));
    m_userParams.append(new simModelElement("Natural frequency", SE_double, static_cast<void*>(&m_naturalfreq), 2));
    m_userParams.append(new simModelElement("Damping",           SE_double, static_cast<void*>(&m_damping),     2));
    m_userParams.append(new simModelElement("Input",             SE_group,  nullptr));
    m_userParams.append(new simModelElement("Target",            SE_double, static_cast<void*>(&m_targ),        2));
    /********************* *********************/
}

double RadSectoRPM(double rads)
{
    return ((rads / (2.0 * M_PI)) * 60.0);
}

double RPMtoRadSec(double rpm)
{
    return ((rpm * (2.0 * M_PI)) / 60.0);
}

double max(double a, double b, double c)
{
   double max = (a < b) ? b : a;
   return ((max < c) ? c : max);
}

double min(double a, double b, double c)
{
   double min = (a < b ) ? a : b;
   return ((min < c) ? min : c);
}

void simModel::startSim(void)
{
    // Test specific initialization

    // Init sim vars
    m_t = 0;
    int m_step = static_cast<int>(m_duration / m_ts);


    // Init sink-source-transfer
    SSScope fScope("Out");
    STFIntegrator d2yInt(m_ts), dyInt(m_ts);

    // Init state
    m_yprev  = 0.0;
    m_dyprev = 0.0;

    // Main cycle
    for (int i = 0; i < m_step; i++)
    {
        // Execution of sink and source
        double x = m_targ;
        double dx = 0.0;
        double d2y = (2.0 * m_damping * m_naturalfreq * dx) +
                     (m_naturalfreq * m_naturalfreq * x) -
                     (2.0 * m_damping * m_naturalfreq * m_dyprev) -
                     (m_naturalfreq * m_naturalfreq * m_yprev);
        SDataVector dy = d2yInt.execute(SDataVector(d2y));
        m_dyprev = dy.value();
        SDataVector y  = dyInt.execute(dy);
        m_yprev = y.value();
        fScope.execute(m_t, y);

        // Update of simutaion variables
        m_t += m_ts;

        // Update progress
        emit updateProgress(static_cast<double>(i+1)/static_cast<double>(m_step));
    }

    fScope.scopeUpdate();

}
