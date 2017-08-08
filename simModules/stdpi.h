#ifndef STDPI_H
#define STDPI_H

#include "simModules/stransfer.h"

class STDPI : public STransfer
{
public:
    STDPI(double kp, double ki);

    SDataVector execute(SDataVector in);

private:
    double m_kp;
    double m_ki;

    double m_intTerm;
};

#endif // STDPI_H
