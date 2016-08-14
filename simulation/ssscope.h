#ifndef SSSCOPE_H
#define SSSCOPE_H

#include "ssink.h"
#include "wscope/wscope.h"

class SSScope : public SSink
{
public:
    SSScope(int tracks = 1);

    void execute(double t, SDataVector in);
    void scopeUpdate(double dt);

private:
    WScope* m_wscope;
};

#endif // SSSCOPE_H
