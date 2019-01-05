/*
 * Application.c
 *
 *  Created on: 04.03.2016
 *      Author: Erich Styger
 */

#include "Application.h"
#include "LED1.h"
#include "WAIT1.h"
#include "CLS1.h"
#include "PORT_PDD.h"
#include "Shell.h"

void APP_Start(void) {
  WAIT1_Waitms(100); /* give sensor time to power up */
  /* need pull-up on UART Rx pin (PTC3) on tinyK20 */
  PORT_PDD_SetPinPullSelect(PORTC_BASE_PTR, 3, PORT_PDD_PULL_UP);
  PORT_PDD_SetPinPullEnable(PORTC_BASE_PTR, 3, PORT_PDD_PULL_ENABLE);

  CLS1_SendStr("\r\n*****************************\r\nLittleFS with tinyK20\r\n*****************************\r\n", CLS1_GetStdio()->stdOut);
  for(;;) { /* main loop */
    LED1_Neg();
    WAIT1_Waitms(50);
    SHELL_Parse(); /* call command line parser */
  }
}
