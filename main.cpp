#include "gsim.h"
#include "simTemplates/simView/commonSimView.h"
#include <QApplication>

#include "simModel/inc/gsimmodel_global.h"
#include "simModel/inc/simModel.h"

//#include "wplot.h"
#include "mwplot.h"

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

    //WPlot w_p1;
    //w_p1.show();
    MWPlot mw_pl;
    mw_pl.show();

    return a.exec();
}
