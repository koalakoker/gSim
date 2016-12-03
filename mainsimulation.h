#ifndef MAINSIMULATION_H
#define MAINSIMULATION_H

#include <QObject>

class mainSimulation : public QObject
{
    Q_OBJECT

public:
    mainSimulation();
    virtual void startSimulation(void) = 0;
    double duration(){return m_duration;}
    void setDuration(double duration){m_duration = duration;}
    double simulationTime(){return m_ts;}
    void setSimulationTime(double ts){m_ts = ts;}
    double controlTime(){return m_tc;}
    void setControlTime(double tc){m_tc = tc;}

    /* Specific params for simulation 7 */
    double m_pi_kp;
    double m_pi_ki;
    double m_pi_kd;
    double m_pi_n;

    double m_r;
    double m_l;

    int m_simulation;

protected:
    double m_t;
    double m_ts;
    double m_tc;
    double m_duration;

private:
    void testSimulation0();
    void testSimulation1();
    void testSimulation2();
    void testSimulation3();
    void testSimulation4();
    void testSimulation5();
    void testSimulation6();
    void initSimulation7();
    void testSimulation7();

signals:
    void updateProgress(double percentage);
};

#endif // MAINSIMULATION_H
