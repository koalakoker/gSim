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

    WPlot w_p1("scope_abcCurr.txt",1), w_p2("scope_abcCurr.txt",2), w_p3("scope_abcCurr.txt",3);
    w_p1.show();
    w_p2.show();
    w_p3.show();

    return a.exec();
}
