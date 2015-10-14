/** ###################################################################
**     Filename  : AnalogDigital.C
**     Project   : TWR_LCD_JM128
**     Processor : MCF51JM128VLH
**     Compiler  : CodeWarrior ColdFireV1 C Compiler
**     Date/Time : 13.02.2010, 17:50
**     Contents  :
**         User source code
**
** ###################################################################*/

/* MODULE AnalogDigital */

#include "Platform.h"
#include "AnalogDigital.h"
#if PL_USE_RTOS
  #include "FRTOS1.h"
#endif

#if PL_USE_RTOS
  static xSemaphoreHandle AD_deviceMutex;
#endif

void AD_GetDevice(void) {
#if PL_USE_RTOS
  FRTOS1_xSemaphoreTake(AD_deviceMutex, portMAX_DELAY);
#endif
}

void AD_GiveDevice(void) {
#if PL_USE_RTOS
  FRTOS1_xSemaphoreGive(AD_deviceMutex);
#endif
}

void AD_Init(void) {
#if PL_USE_RTOS
  AD_deviceMutex = FRTOS1_xSemaphoreCreateMutex();
#endif
}

/* END AnalogDigital */
