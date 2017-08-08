#include "gsim.h"
#include "simTemplates/simModel/simModel8.h"
#include "simTemplates/simView/simView8.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    gSim w;
    simModel8 m;
    simView8 s;

    s.setSimModel(&m);
    s.updateView();
    s.show();

    w.setSimModel(&m);
    w.setSimView(&s);
    w.show();

    return a.exec();
}
