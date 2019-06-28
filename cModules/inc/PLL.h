#ifndef PLL_H
#define PLL_H

#include "MC_type.h"
#include "PI.h"

typedef struct
{
  PIReg pi;
  int16_t hTheta;
  int16_t hSpeedDpp;
} PLL;

int16_t PLL_Calc(PLL *handle, int16_t hSin, int16_t hCos);

#endif /* PLL_H */
