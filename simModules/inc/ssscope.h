#ifndef SSSCOPE_H
#define SSSCOPE_H

#include "simmodules_global.h"

#include <QString>
#include "ssink.h"
#include "mwplot.h"

class SIMMODULESSHARED_EXPORT SSScope : public SSink
{
public:
    SSScope(QString name, int tracks = 1);

    void execute(double t, SDataVector in);
    void scopeUpdate(double dt);
    void exportData(QString fileName);

private:
    MWPlot* m_mwplot;
};

#endif // SSSCOPE_H
