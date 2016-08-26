#include "staritmetic.h"

STAritmetic::STAritmetic(aritmeticType_t aritmeticType)
{
    m_aritmeticType = aritmeticType;
}

SDataVector STAritmetic::execute(SDataVector in1, SDataVector in2)
{
    double x = in1.value();
    double y = in2.value();
    double z = 0; // Result of operation
    switch (m_aritmeticType) {
    case sumType:
        {
            z = x + y;
        }
        break;
    case differenceType:
        {
            z = x - y;
        }
        break;
    case multiplicationType:
        {
            z = x * y;
        }
        break;
    case divisionType:
        {
            z = x / y;
        }
        break;
    default:
        break;
    }
    return SDataVector(z);
}
