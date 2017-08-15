#ifndef SSSCOPE_H
#define SSSCOPE_H

#include <QString>
#include "ssink.h"
#include "wscope.h"

class SSScope : public SSink
{
public:
    SSScope(QString name, int tracks = 1);

    void execute(double t, SDataVector in);
    void scopeUpdate(double dt);

private:
    WScope* m_wscope;
};

#endif // SSSCOPE_H
