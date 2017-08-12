#include "gsim.h"
#include "simTemplates/simView/commonSimView.h"
#include <QApplication>

#include "simTemplates/simModel/simModel9.h"    /* Update here for any new model */

/****************** Legacy ******************/
/*------------- Model 7 (SVM)  -------------*/
//#include "simTemplates/simModel/simModel7.h"
//#include "simTemplates/simView/simView7.h"
/*----------- Model 8 (Resolver) -----------*/
//#include "simTemplates/simModel/simModel8.h"
//#include "simTemplates/simView/simView8.h"
/********************************************/

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    gSim w;
    commonSimView v;
    simModel9 m;                                /* Update here for any new model */

/****************** Legacy ******************/
/*------------- Model 7 (SVM)  -------------*/
//  simModel7 m;
//  simView7 v;
/*----------- Model 8 (Resolver) -----------*/
//  simModel8 m;
//  simView8 v;
/********************************************/

    v.setSimModel(&m);
    v.updateView();

    w.setSimModel(&m);
    w.setSimView(&v);

    w.show();

    return a.exec();
}
