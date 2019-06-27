#ifndef SSSCOPE_H
#define SSSCOPE_H

#include <QString>
#include "ssink.h"
#include "plotterwindow.h"

class SSScope : public SSink
{
public:
    PlotterWindow* createScope(QString name);

    void execute(double t, SDataVector in);
    void scopeUpdate(void);
    void exportData(QString fileName);

private:
    SSScope();
    PlotterWindow* m_mwplot;
};

#endif // SSSCOPE_H
