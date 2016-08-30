#ifndef MAINSIMULATOR_H
#define MAINSIMULATOR_H

#include <QObject>

class mainSimulator : public QObject
{
    Q_OBJECT

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
    double m_pi_kd;
    double m_pi_n;

    double m_r;
    double m_l;

    int m_simulation;

private:
    double m_t;

    double m_ts;
    double m_tc;
    double m_duration;

    void testSimulation0();
    void testSimulation1();
    void testSimulation2();
    void testSimulation3();
    void testSimulation4();
    void testSimulation5();
    void testSimulation6();
    void testSimulation7();

signals:
    void updateProgress(double percentage);
};

#endif // MAINSIMULATOR_H
