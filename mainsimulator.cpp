#include "mainsimulator.h"

mainSimulator::mainSimulator()
{
    t = 0;
    dt = 0.001;
    duration = 1;
}

void mainSimulator::startSimulation(void)
{
    if (!scope1.isVisible())
    {
        scope1.show();
    }



    t = 0;
    step = (int)(duration / dt);

    int i;

    for (i = 0; i < step; i++)
    {
        double y = func1.calc(t);
        scope1.addPoint(t, y);
        t += dt;
    }
}
