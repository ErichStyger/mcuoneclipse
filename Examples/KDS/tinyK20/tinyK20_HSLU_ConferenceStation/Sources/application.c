/*
 * application.c
 *
 *  Created on: 03.08.2020
 *      Author: Erich Styger Local
 */

#include "application.h"
#include "FRTOS1.h"

void APP_Run(void) {
  vTaskStartScheduler();
  for(;;) {
    __asm("nop");
  }
}


