/*
 * Application.c
 *
 *  Created on: 04.03.2016
 *      Author: Erich Styger
 */

#include "Application.h"
#include "VL6180X.h"
#include "LED1.h"
#include "WAIT1.h"
#include "CLS1.h"

void APP_Start(void) {
  uint8_t val=0;
  uint8_t range, res;
  uint16_t ambient;
  CLS1_ConstStdIOType *io = CLS1_GetStdio();

  VL_Init(); /* initialize sensor driver */
  for(;;) {
    res = VL_ReadRangeSingle(&range);
    if (res!=ERR_OK) {
      CLS1_SendStr("ERROR Range: ", io->stdErr);
      CLS1_SendNum8u(res, io->stdErr);
    } else {
      CLS1_SendStr("Range: ", io->stdOut);
      CLS1_SendNum8u(range, io->stdOut);
    }
    res = VL_ReadAmbientSingle(&ambient);
    if (res!=ERR_OK) {
      CLS1_SendStr(" ERROR Ambient: ", io->stdErr);
      CLS1_SendNum8u(res, io->stdErr);
    } else {
      CLS1_SendStr(" Ambient: ", io->stdOut);
      CLS1_SendNum16u(ambient, io->stdOut);
    }
    CLS1_SendStr("\r\n", io->stdOut);
    LED1_Neg();
    WAIT1_Waitms(500);
  }
}


