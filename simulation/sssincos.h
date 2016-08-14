#ifndef SSSIN_H
#define SSSIN_H

#include "ssource.h"

class SSSinCos : public SSource
{
public:
    typedef enum {sinType, cosType} trigType_t;

    SSSinCos(trigType_t trigType = sinType, double amplitude = 1, double frequency = 1);
    SDataVector execute(double t);

private:
    double m_amplitude;
    double m_frequency;
    trigType_t m_trigType;
};

#endif // SSSIN_H
