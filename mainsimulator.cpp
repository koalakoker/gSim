#include "mainsimulator.h"

mainSimulator::mainSimulator()
{
    t = 0;
    dt = 0.001;
    duration = 1;
}

void mainSimulator::startSimulation(void)
{
    t = 0;
    step = (int)(duration / dt);

    int i;

    for (i = 0; i < step; i++)
    {
        double y = func1.calc(t);
        scope1.addPoint(t, y);
        t += dt;
    }

    scope1.show();
    scope1.refresh();
}
