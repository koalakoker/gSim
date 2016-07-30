#ifndef MAINSIMULATOR_H
#define MAINSIMULATOR_H

#include "wscope.h"
#include "mathfunction.h"

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
    WScope scope1;
    mathFunction func1;
};

#endif // MAINSIMULATOR_H
