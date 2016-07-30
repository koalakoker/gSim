#include "gsim.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    gSim w;
    w.show();

    return a.exec();
}
