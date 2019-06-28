#ifndef PI_H
#define PI_H

#include <stdint.h>

typedef struct
{
  int16_t hKpGain;
  int16_t hKiGain;
  int32_t wIntegralTerm;

  int16_t hUpperLimit;
  int16_t hKpDivisor;
  int16_t hKiDivisor;
  int32_t wUpperIntegralLimit;
  int32_t wLowerIntegralLimit;
  
} PIReg;


int16_t PI_Calc(PIReg *handle, int32_t wProcessVarError);


#endif /* PI_H */
