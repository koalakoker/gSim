#ifndef SSSIN_H
#define SSSIN_H

#include "ssource.h"

class SSSinCos : public SSource
{
public:
    typedef enum {sinType, cosType} trigType_t;

    SSSinCos(trigType_t trigType = sinType, double frequency = 1, double amplitude = 1);
    SDataVector execute(double t);

    double amplitude(){return m_amplitude;}
    void setAmplitude(double amplitude){m_amplitude = amplitude;}
    double frequency(){return m_frequency;}
    void setFrequency(double frequency){m_frequency = frequency;}

private:
    double m_amplitude;
    double m_frequency;
    trigType_t m_trigType;
};

#endif // SSSIN_H
