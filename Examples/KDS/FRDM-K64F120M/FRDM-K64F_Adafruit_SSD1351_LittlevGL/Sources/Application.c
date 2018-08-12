/*
 * Application.c
 *
 *  Created on: 20.03.2017
 *      Author: Erich Styger
 *       */

#include "Application.h"
#include "LED1.h"
#include "LED2.h"
#include "LED3.h"
#include "WAIT1.h"
#include "LCD1.h"
#include "FRTOS1.h"

#include "gui.h"

void APP_Run(void) {
  GUI_Init();
  vTaskStartScheduler();
  for(;;) {

  }
}


