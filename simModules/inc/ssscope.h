#ifndef SSSCOPE_H
#define SSSCOPE_H

#include "simmodules_global.h"

#include <QString>
#include "ssink.h"
#include "wscope.h"

class SIMMODULESSHARED_EXPORT SSScope : public SSink
{
public:
    SSScope(QString name, int tracks = 1);

    void execute(double t, SDataVector in);
    void scopeUpdate(double dt);
    void exportData(QString fileName);

private:
    WScope* m_wscope;
};

#endif // SSSCOPE_H
