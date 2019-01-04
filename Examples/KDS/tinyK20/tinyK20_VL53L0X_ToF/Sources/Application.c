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
#include "vl53l0x.h"

void APP_Start(void) {
  int16_t mm;
  uint8_t res;
  int cntr;

  WAIT1_Waitms(100); /* give sensor time to power up */
  /* need pull-up on UART Rx pin (PTC3) on tinyK20 */
  PORT_PDD_SetPinPullSelect(PORTC_BASE_PTR, 3, PORT_PDD_PULL_UP);
  PORT_PDD_SetPinPullEnable(PORTC_BASE_PTR, 3, PORT_PDD_PULL_ENABLE);

  CLS1_SendStr("\r\n*****************************\r\nVL53L0X with tinyK20\r\n*****************************\r\n", CLS1_GetStdio()->stdOut);
  /* initialization */
  do {
    res = VL53L0X_Init();
    if (res!=ERR_OK) {
      CLS1_SendStr("ERROR: failed VL53L0X_Init()!\r\n", CLS1_GetStdio()->stdOut);
      WAIT1_Waitms(1000);
    }
  } while(res!=ERR_OK);

  cntr = 0;
  for(;;) { /* main loop */
    cntr++;
    if (cntr>60) { /* slow down measurements */
      cntr = 0;
      do {
        res = VL53L0X_MeasureSingle(&mm);
        if (res!=ERR_OK) {
          CLS1_SendStr("ERROR: failed VL53L0X_MeasureSingle()!\r\n", CLS1_GetStdio()->stdOut);
          WAIT1_Waitms(1000);
        }
      } while(res!=ERR_OK);
      CLS1_printf("\r\nRange: %dmm\r\n", mm);
    }
    LED1_Neg();
    WAIT1_Waitms(50);
    SHELL_Parse(); /* call command line parser */
  }
}
