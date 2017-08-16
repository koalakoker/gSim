#ifndef STFDISCRETEFIRSTORDER_H
#define STFDISCRETEFIRSTORDER_H

#include "simmodules_global.h"

#include "stransfer.h"

class SIMMODULESSHARED_EXPORT STFDiscreteFirstOrder : public STransfer
{
public:
    STFDiscreteFirstOrder(double b0 = 0, double b1 = 0, double a1 = 0); // H(Z) = Y(Z)/X(Z) = (b0 + b1 * z^-1) / (1 + a1 * z^-1)

    SDataVector execute(SDataVector in);

private:
    double m_b0;
    double m_b1;
    double m_a1;

    double m_yPrev;
    double m_xPrev;
};

#endif // STFDISCRETEFIRSTORDER_H
