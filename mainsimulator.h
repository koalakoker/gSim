#ifndef MAINSIMULATOR_H
#define MAINSIMULATOR_H

class mainSimulator
{
public:
    mainSimulator();
    void startSimulation(void);
    double duration(){return m_duration;}
    void setDuration(double duration){m_duration = duration;}
    double simulationTime(){return m_ts;}
    void setSimulationTime(double ts){m_ts = ts;}
    double controlTime(){return m_tc;}
    void setControlTime(double tc){m_tc = tc;}

    double m_pi_kp;
    double m_pi_ki;

    double m_r;
    double m_l;

private:
    double m_t;

    double m_ts;
    double m_tc;
    double m_duration;

    void testSimulation0();
    void testSimulation1();
    void testSimulation2();
    void testSimulation3();
};

#endif // MAINSIMULATOR_H
