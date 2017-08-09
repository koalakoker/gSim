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

    w.setSimModel(&m);
    w.setSimView(&s);

    w.show();
    s.show();

    return a.exec();
}
