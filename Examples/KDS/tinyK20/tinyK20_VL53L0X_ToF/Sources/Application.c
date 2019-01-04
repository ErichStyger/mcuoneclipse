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
#include "vl53l0x.h"

void APP_Start(void) {
  int16_t mm;
  uint8_t res;

  /* need pull-up on UART Rx pin (PTC3) on tinyK22 */
  PORT_PDD_SetPinPullSelect(PORTC_BASE_PTR, 3, PORT_PDD_PULL_UP);
  PORT_PDD_SetPinPullEnable(PORTC_BASE_PTR, 3, PORT_PDD_PULL_ENABLE);

  CLS1_SendStr("\r\n*****************************\r\nVL53L0X with tinyK20\r\n*****************************\r\n", CLS1_GetStdio()->stdOut);
  do {
    res = VL53L0X_Init();
    if (res!=ERR_OK) {
      CLS1_SendStr("ERROR: failed VL53L0X_Init()!\r\n", CLS1_GetStdio()->stdOut);
      WAIT1_Waitms(1000);
    }
  } while(res!=ERR_OK);

  for(;;) { /* main loop */
    do {
      res = VL53L0X_MeasureSingle(&mm);
      if (res!=ERR_OK) {
        CLS1_SendStr("ERROR: failed VL53L0X_MeasureSingle()!\r\n", CLS1_GetStdio()->stdOut);
        WAIT1_Waitms(1000);
      }
    } while(res!=ERR_OK);
    CLS1_printf("Range in mm: %d\r\n", mm);
    LED1_Neg();
    WAIT1_Waitms(500);
  }
}
