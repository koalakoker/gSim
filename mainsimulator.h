#ifndef MAINSIMULATOR_H
#define MAINSIMULATOR_H

class mainSimulator
{
public:
    mainSimulator();
    void startSimulation(void);

private:
    double t;
    double dt;
    double duration;
    int step;

    void testSimulation0();
    void testSimulation1();
    void testSimulation2();
    void testSimulation3();
};

#endif // MAINSIMULATOR_H
