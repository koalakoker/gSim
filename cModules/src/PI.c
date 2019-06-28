#include "cModules\inc\PI.h"

int16_t PI_Calc(PIReg *handle, int32_t wProcessVarError)
{
  int32_t wProportional_Term, wIntegral, wOutput_32,wIntegral_sum_temp;
  int32_t wDischarge = 0;
  int16_t hUpperOutputLimit = handle->hUpperLimit;
  int16_t hLowerOutputLimit = -handle->hUpperLimit;
  
  /* Proportional term computation*/
  wProportional_Term = handle->hKpGain * wProcessVarError;
  
  /* Integral term computation */
  if (handle->hKiGain == 0)
  {
    handle->wIntegralTerm = 0;
  }
  else
  { 
    wIntegral = handle->hKiGain * wProcessVarError;
    wIntegral_sum_temp = handle->wIntegralTerm + wIntegral;
    
    if (wIntegral_sum_temp < 0)
    {
      if (handle->wIntegralTerm > 0)
      {
        if (wIntegral > 0)
        {
          wIntegral_sum_temp = INT32_MAX;
        }
      }
    }
    else
    {
      if (handle->wIntegralTerm < 0)
      {
        if (wIntegral < 0)
        {
          wIntegral_sum_temp = -INT32_MAX;
        }
      }
    }		

    if (wIntegral_sum_temp > handle->wUpperIntegralLimit)
    {
      handle->wIntegralTerm = handle->wUpperIntegralLimit;
    }
    else if (wIntegral_sum_temp < handle->wLowerIntegralLimit)
    { 
      handle->wIntegralTerm = handle->wLowerIntegralLimit;
    }
    else
    {
      handle->wIntegralTerm = wIntegral_sum_temp;
    }
  }
  
  wOutput_32 = (wProportional_Term/(int32_t)(handle->hKpDivisor))+
               (handle->wIntegralTerm/(int32_t)(handle->hKiDivisor));

  if (wOutput_32 > hUpperOutputLimit)
  {
    
    wDischarge = hUpperOutputLimit - wOutput_32;
    wOutput_32 = hUpperOutputLimit;		  			 	
  }
  else if (wOutput_32 < hLowerOutputLimit)
  {
    
    wDischarge = hLowerOutputLimit - wOutput_32; 
    wOutput_32 = hLowerOutputLimit;
  }
  else
  {}
  
  handle->wIntegralTerm += wDischarge;
  
  return((int16_t)(wOutput_32)); 	
}
