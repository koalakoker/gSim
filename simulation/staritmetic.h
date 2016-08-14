#ifndef STARITMETIC_H
#define STARITMETIC_H

#include "simulation/stransferbinary.h"

class STAritmetic : public STransferBinary
{
public:
    typedef enum {sumType, differenceType, multiplicationType, divisionType} aritmeticType_t;

    STAritmetic(aritmeticType_t aritmeticType);

    SDataVector execute(SDataVector in1, SDataVector in2);

private:
    aritmeticType_t m_aritmeticType;
};

#endif // STARITMETIC_H
