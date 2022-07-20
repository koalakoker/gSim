#ifndef SSSCOPE_H
#define SSSCOPE_H

#include "simmodules_global.h"

#include <QString>
#include "ssink.h"
#include "wplot/wplot.h"

class SIMMODULESSHARED_EXPORT SSScope : public SSink
{
public:
    SSScope(QString name);

    void execute(double t, SDataVector in);
    void scopeUpdate(void);
    void exportData(QString fileName);

private:
    WPlot* m_wplot;
};

#endif // SSSCOPE_H
