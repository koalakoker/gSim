#include "cModules/inc/PLL.h"
#include "cModules/inc/mc_math.h"

int16_t PLL_Calc(PLL *handle, int16_t hSin, int16_t hCos)
{
  int32_t wSinCos, wCosSin;
  int16_t hRotor_Speed;
  Trig_Components trigComp;
  int16_t hSinCos, hCosSin;
    
  trigComp = MCM_Trig_Functions(handle->hTheta); // Theta*

  /* Alfa & Beta BEMF multiplied by Cos & Sin*/
  wSinCos = (int32_t)(hSin)*(int32_t)trigComp.hCos;
  wCosSin = (int32_t)(hCos)*(int32_t)trigComp.hSin;

#ifdef FULL_MISRA_C_COMPLIANCY
  hSinCos = (int16_t)(wSinCos/32768); 
#else
  hSinCos = (int16_t)(wSinCos >> 15);
#endif  

#ifdef FULL_MISRA_C_COMPLIANCY
  hCosSin = (int16_t)(wCosSin/32768);
#else
  hCosSin = (int16_t)(wCosSin >> 15);
#endif
  
  /* Speed PI regulator */
  hRotor_Speed = PI_Calc(&(handle->pi), (int32_t)(hSinCos)-(int32_t)(hCosSin));

  handle->hTheta   += hRotor_Speed;
  handle->hSpeedDpp = hRotor_Speed;
  
  return (hRotor_Speed);
}
