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

    scope1 = new WScope(2);

    for (int i = 0; i < step; i++)
    {
        QVector<double> data;
        data.append(func1.calc(t));
        data.append(func2.calc(t));

        scope1->addPoint(t, data);

        t += dt;
    }

    scope1->setdt(dt);
    scope1->show();
    scope1->refresh();
}
