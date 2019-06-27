#include "simModel.h"

#include "stpi.h"
#include "stfintegrator.h"
#include "math.h"

# define M_PI           3.14159265358979323846  /* pi */

simModel::simModel()
{
    /* Set sim number */
    m_sim = 0;
    m_description = "Second order system";

    /* Default common params */
    m_duration = 0.0004;
    m_ts = m_duration / 100;

    /* Specific params for sim */
    m_naturalfreq = 25000; // rad/s
    m_damping = 0.7;
    m_teta = 1.0;
    //m_acc = 10000000.0000;
    m_acc = 0;

    /********************* *********************/
    /*      Setup parameters into the view     */
    /********************* *********************/
    m_userParams.append(new simModelElement("Params",            SE_group,  nullptr));
    m_userParams.append(new simModelElement("Natural frequency", SE_double, static_cast<void*>(&m_naturalfreq), 2));
    m_userParams.append(new simModelElement("Damping",           SE_double, static_cast<void*>(&m_damping),     2));
    m_userParams.append(new simModelElement("Input",             SE_group,  nullptr));
    m_userParams.append(new simModelElement("Start Teta",        SE_double, static_cast<void*>(&m_teta),        2));
    m_userParams.append(new simModelElement("Acceleration",      SE_double, static_cast<void*>(&m_acc),         4));
    m_userParams.append(new simModelElement("Pll",               SE_group,  nullptr));
    m_userParams.append(new simModelElement("Kp",                SE_double, static_cast<void*>(&m_pllKp),       2));
    m_userParams.append(new simModelElement("Ki",                SE_double, static_cast<void*>(&m_pllKi),       2));
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
    SSScope* fScope = createScope("Out");

    STFIntegrator tetaInt(m_ts, m_teta),omegaInt(m_ts), d2yInt(m_ts), dyInt(m_ts);

    // PLL
    m_pllKp = 2 * m_naturalfreq * m_damping;
    m_pllKi = m_naturalfreq * m_naturalfreq;
    STPI pllPI(m_pllKp, m_pllKi,m_ts);
    STFIntegrator pllInt(m_ts);

    // Init others
    m_k  = sqrt(1-(m_damping*m_damping));
    m_wd = m_naturalfreq * m_k;
    m_th = atan2(m_wd,(m_damping*m_naturalfreq));

    // Init state
    m_omega = 0.0;

    m_yprev  = 0.0;
    m_dyprev = 0.0;

    // Init PLL
    m_tetaEst = 0.0;

    // Main cycle
    for (int i = 0; i < m_step; i++)
    {
        // Execution of sink and source

        // Second order simulation
        double x = m_teta;
        double dx;
        if (i == 0)
        {
            x = 0;
            dx = 0;
        }
        else if (i == 1)
        {
            x = m_teta;
            dx = m_teta / m_ts;
        } else
        {
            x = m_teta;
            dx = m_omega;
        }

        double d2y = (2.0 * m_damping * m_naturalfreq * dx) +
                     (m_naturalfreq * m_naturalfreq * x) -
                     (2.0 * m_damping * m_naturalfreq * m_dyprev) -
                     (m_naturalfreq * m_naturalfreq * m_yprev);
        SDataVector dy = d2yInt.execute(SDataVector(d2y));
        m_dyprev = dy.value();
        SDataVector y  = dyInt.execute(dy);
        m_yprev = y.value();


        // PLL
        if (i > 0)
        {
            double err = m_teta - m_tetaEst;
            double omegaEst = pllPI.execute(err).value();
            m_tetaEst = pllInt.execute(omegaEst).value();
        }

        // Dominio del tempo formula chiusa

        double yt = 1.0 + (exp(-m_damping * m_naturalfreq * m_t) *
                           sin((m_wd * m_t) - m_th) /
                           m_k);

        fScope->execute(m_t, SDataVector(x, y.value(), yt, m_tetaEst));

        // Omega integration
        if (i > 0)
        {
            if (m_t < 0.0003)
            {
                m_omega = omegaInt.execute(m_acc).  value();
            }
            m_teta  = tetaInt. execute(m_omega).value();
        }

        // Update of simutaion variables
        m_t += m_ts;

        // Update progress
        emit updateProgress(static_cast<double>(i+1)/static_cast<double>(m_step));
    }

    fScope->scopeUpdate();

}
