#ifndef SSSIN_H
#define SSSIN_H

#include "ssource.h"

class SSSin : public SSource
{
public:
    SSSin();

    SDataVector execute(double t);

    double amplitude() {return m_amplitude;}
    void setAmplitude(double amplitude) {m_amplitude = amplitude;}
    double frequency() {return m_frequency;}
    void setFrequency(double frequency) {m_frequency = frequency;}

private:
    double m_amplitude;
    double m_frequency;
};

#endif // SSSIN_H
