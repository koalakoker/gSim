#include "gsim.h"
#include "simTemplates/simView/commonSimView.h"
#include <QApplication>

#include "simTemplates/simModel/simModel9.h"    /* Update here for any new model */

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    gSim w;
    commonSimView v;

    simModel9 m;                                /* Update here for any new model */

    v.setSimModel(&m);
    v.updateView();

    w.setSimModel(&m);
    w.setSimView(&v);

    w.show();

    return a.exec();
}
