#ifndef SSSCOPE_H
#define SSSCOPE_H

#include <QString>
#include "ssink.h"
#include "plotterwindow.h"

class SSScope : public SSink
{
public:
    SSScope();
    PlotterWindow* createScope(QString name);

    void execute(double t, SDataVector in);
    void scopeUpdate(void);
    void exportData(QString fileName);

private:
    PlotterWindow* m_mwplot;
};

#endif // SSSCOPE_H
