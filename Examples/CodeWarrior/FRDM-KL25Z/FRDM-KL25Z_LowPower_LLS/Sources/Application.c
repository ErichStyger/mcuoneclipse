/*
 * Application.c
 *
 *  Created on: Mar 16, 2014
 *      Author: Erich Styger
 */

#include "Application.h"
#include "LED1.h"
#include "LED2.h"
#include "LED3.h"
#include "WAIT1.h"
#include "LPTMR_PDD.h"

void APP_OnLLSWakeUpInterrupt(void) {
  uint32_t tmp;
  
  tmp = Cpu_GetLLSWakeUpFlags();
  if (tmp&LLWU_INT_MODULE0) { /* LPTMR */
    LPTMR_PDD_ClearInterruptFlag(LPTMR0_BASE_PTR); /* Clear interrupt flag */
  }
}

void APP_TimerInterrupt(void) {
  LED1_Neg(); /* red LED */
}

void APP_Run(void) {
  LED2_On();
  WAIT1_Waitms(1000);
  LED2_Off();
  for(;;) {
    //LED3_Neg(); /* blue LED */
    //Cpu_SetOperationMode(DOM_WAIT, NULL, NULL); /* next interrupt will wake us up */
    //Cpu_SetOperationMode(DOM_SLEEP, NULL, NULL); /* next interrupt will wake us up */
    Cpu_SetOperationMode(DOM_STOP, NULL, NULL); /* next interrupt will wake us up */
  }
}
