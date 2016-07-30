#include "gsim.h"
#include <QApplication>

#include "wscope.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    gSim w;
//    w.show();

    WScope sc;
    sc.show();

    return a.exec();
}
