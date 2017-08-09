#include "gsim.h"
#include "simTemplates/simModel/simModel8.h"
#include "simTemplates/simView/simView8.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    gSim w;
    simModel8 m;
    simView8 v;

    v.setSimModel(&m);
    v.updateView();

    w.setSimModel(&m);
    w.setSimView(&v);

    w.show();
    v.show();

    return a.exec();
}
