/*
 * Application.c
 *
 *  Created on: 20.09.2015
 *      Author: tastyger
 */

#include "Application.h"
#include "LED1.h"
#include "LED2.h"
#include "LED3.h"
#include "FRTOS1.h"

void APP_Run(void) {
  LED1_On();
  LED1_Off();
  LED2_On();
  LED2_Off();
  LED3_On();
  LED3_Off();
  FRTOS1_vTaskStartScheduler();
  for(;;) {}
}


