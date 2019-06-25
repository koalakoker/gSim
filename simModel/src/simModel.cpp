#include "simModel.h"

#include "stpmsmabc.h"
#include "strl.h"
#include "stdpi.h"
#include "stdpid.h"
#include "stpid.h"
#include "plot\ssscope.h"
#include "math.h"

# define M_PI           3.14159265358979323846  /* pi */

simModel::simModel()
{
    /* Set sim number */
    m_sim = 0;
    m_description = "Friction model";

    /* Default common params */
    m_ts = 1/100000.0;
    m_duration = 1.0;

    /* Specific params for sim */
    m_fbrk = 0.018;
    m_wbrk = 24.54/4;
    m_fc   = 0.0071;
    m_f    = 0.0000163;

    m_maxw = (4000.0 / 60.0) * 2.0 * M_PI;
    m_acc  = (2.0 * m_maxw) / m_duration;

    /********************* *********************/
    /*      Setup parameters into the view     */
    /********************* *********************/
    m_userParams.append(new simModelElement("Meccanical Frictions",   SE_group,  nullptr));
    m_userParams.append(new simModelElement("Fbrk", SE_double, static_cast<void*>(&m_fbrk), 4));
    m_userParams.append(new simModelElement("Wbrk", SE_double, static_cast<void*>(&m_wbrk), 2));
    m_userParams.append(new simModelElement("Fc",   SE_double, static_cast<void*>(&m_fc)  , 4));
    m_userParams.append(new simModelElement("f",    SE_double, static_cast<void*>(&m_f)   , 7));

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
    SSScope fScope("Friction");

    // Main cycle
    for (int i = 0; i < m_step; i++)
    {
        // Execution of sink and source
        double w = (m_t * m_acc) - m_maxw;
        double f;
        if (w > 0.0)
        {
            f = m_fc + (m_f * w);
        }
        else {
            f = -m_fc + (m_f * w);
        }
        double s2e = 2.3316439815971242034;
        double wst = m_wbrk * sqrt(2.0);
        double wc  = m_wbrk / 10.0;
        double f2  = s2e * (m_fbrk - m_fc) * exp(-((w*w)/(wst*wst))) * (w/wst) +
                     m_fc * tanh(w/wc) +
                     (m_f * w);
        fScope.execute(m_t, SDataVector(w,f,f2));

        // Update of simutaion variables
        m_t += m_ts;

        // Update progress
        emit updateProgress(static_cast<double>(i+1)/static_cast<double>(m_step));
    }

    fScope.scopeUpdate();

}
