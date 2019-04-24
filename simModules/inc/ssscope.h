#ifndef SSSCOPE_H
#define SSSCOPE_H

#include "simmodules_global.h"

#include <QString>
#include "ssink.h"
#include "mwplot.h"

class SIMMODULESSHARED_EXPORT SSScope : public SSink
{
public:
    SSScope(QString name, QVector<QWidget*>* pScopes = 0);

    void execute(double t, SDataVector in);
    void scopeUpdate(void);
    void exportData(QString fileName);

private:
    MWPlot* m_mwplot;
};

#endif // SSSCOPE_H
