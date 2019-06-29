#include <QApplication>
#include "simulationmanager.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    SimulationManager simMngr;
    simMngr.show();

    return a.exec();
}
