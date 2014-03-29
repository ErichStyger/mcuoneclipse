/**
 * \file
 * \brief Platform configuration file.
 * \author (c) 2014 Erich Styger, http://mcuoneclipse.com/
 * \note MIT License (http://opensource.org/licenses/mit-license.html)
 */

#include "Platform.h"
#include "Application.h"
#if PL_HAS_SHELL
  #include "Shell.h"
  #include "CLS1.h"
#endif
#if PL_HAS_RTOS
  #include "FRTOS1.h"
#endif
#include "LowPower.h"
#include "LED1.h"
#include "LED2.h"
#include "LED3.h"
#include "WAIT1.h"

#if PL_HAS_RTOS
static portTASK_FUNCTION(BlinkTask, pvParameters) {

  (void)pvParameters; /* not used */
  for(;;) {
    LED2_Neg();
    FRTOS1_vTaskDelay(1000/portTICK_RATE_MS);
#if PL_HAS_SHELL
    CLS1_SendStr((unsigned char*)"hello from blink!\r\n", CLS1_GetStdio()->stdOut);
#endif
  } /* for */
}
#endif /* PL_HAS_RTOS */



void APP_Run(void) {
  LED2_On();
  WAIT1_Waitms(1000); /* blink to indicate reset/power-up situation */
  LED2_Off();
  
#if PL_HAS_LOW_POWER
  LP_Init();
#endif
#if PL_HAS_SHELL
  SHELL_Init();
#endif
#if PL_HAS_RTOS
  if (FRTOS1_xTaskCreate(BlinkTask, "Blink", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL) != pdPASS) {
    for(;;){} /* error */
  }
  FRTOS1_vTaskStartScheduler(); /* does not return */
#else
  for(;;) {
    LP_EnterPowerMode(LP_WAIT);
    LED1_On();
    WAIT1_Waitms(20);
    LED1_Off();
  }
#endif
}
