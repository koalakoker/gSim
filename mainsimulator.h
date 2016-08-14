#ifndef MAINSIMULATOR_H
#define MAINSIMULATOR_H

#include "simulation/sssin.h"
#include "simulation/ssscope.h"

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
};

#endif // MAINSIMULATOR_H
