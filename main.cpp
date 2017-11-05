#include "gsim.h"
#include "simTemplates/simView/commonSimView.h"
#include <QApplication>

#include "simModel/inc/gsimmodel_global.h"
#include "simModel/inc/simModel.h"

#include "wplot.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    gSim w;
    commonSimView v;
    simModel m;

    v.setSimModel(&m);
    v.updateView();

    w.setSimModel(&m);
    w.setSimView(&v);

    w.show();

    WPlot w_p1("model2.txt");
    //WPlot w_p2("scope_abcCurr.txt");
    w_p1.show();
    //w_p2.show();

    return a.exec();
}
