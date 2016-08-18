#ifndef MAINSIMULATOR_H
#define MAINSIMULATOR_H

class mainSimulator
{
public:
    mainSimulator();
    void startSimulation(void);
    double duration(){return m_duration;}
    void setDuration(double duration){m_duration = duration;}
    double stepTime(){return m_dt;}
    void setStepTime(double dt){m_dt = dt;}

private:
    double m_t;
    int m_step;

    double m_dt;
    double m_duration;

    void testSimulation0();
    void testSimulation1();
    void testSimulation2();
    void testSimulation3();
};

#endif // MAINSIMULATOR_H
