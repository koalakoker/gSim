#include "simModelTest.h"

# define M_PI           3.14159265358979323846  /* pi */

simModelTest::simModelTest()
{
    /* Set sim number */
    m_sim = 0;
    m_description = "Test model";

    /* Default common params */
    m_duration = 1.0;
    m_ts = 0.000005;
    m_tc = m_ts * 10;

    /* Specific params for sim */

    /********************* *********************/
    /*      Setup parameters into the view     */
    /********************* *********************/
    //m_userParams.append(new simModelElement("Params",            SE_group,  nullptr));
    //m_userParams.append(new simModelElement("Natural frequency", SE_double, static_cast<void*>(&m_naturalfreq), 2));

    /********************* *********************/
}

//double S16DegreeToRad(int16_t s16degree)
//{
//    return (static_cast<double>(s16degree) * 2.0 * M_PI) / 65536.0;
//}

//int16_t RadToS16Degree(double rad)
//{
//    return static_cast<int16_t>((rad * 65536.0) / (2.0 * M_PI));
//}

//double RadSectoRPM(double rads)
//{
//    return ((rads / (2.0 * M_PI)) * 60.0);
//}

//double RPMtoRadSec(double rpm)
//{
//    return ((rpm * (2.0 * M_PI)) / 60.0);
//}

//double dpp2radSec(int16_t dpp, double freq)
//{
//    return (static_cast<double>(dpp) * freq * 2.0 * M_PI) / 65536.0;
//}

//int16_t radSec2dpp(double radSec, double freq)
//{
//    return static_cast<int16_t>((65536.0 * radSec) / (freq * 2.0 * M_PI));
//}

//double max(double a, double b, double c)
//{
//   double max = (a < b) ? b : a;
//   return ((max < c) ? c : max);
//}

//double min(double a, double b, double c)
//{
//   double min = (a < b ) ? a : b;
//   return ((min < c) ? min : c);
//}

void simModelTest::startSim(void)
{
    // Test specific initialization

    // Init sim vars
    m_t = 0;
    int m_step = static_cast<int>(m_duration / m_ts);
    //int simConRatio = static_cast<int>(m_tc / m_ts);


    // Init sink-source-transfer
    SSScope* fScope   = createScope("Teta");

    // Init state
    double y = 0;

    // Main cycle
    for (int i = 0; i < m_step; i++)
    {
        // Execution of sink and source
        y += 1;
        fScope-> execute(m_t,  y);

        // Update of simutaion variables
        m_t += m_ts;

        // Update progress
        emit updateProgress(static_cast<double>(i+1)/static_cast<double>(m_step));
    }

    fScope-> scopeUpdate();
}
