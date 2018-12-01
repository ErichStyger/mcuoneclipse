/*
 * Application.c
 *
 *  Created on: 27.11.2018
 *      Author: Erich Styger
 */


#include "Application.h"
#include "LED1.h"
#include "WAIT1.h"
#include "Si7021.h"
#include "CLS1.h"
#include "Shell.h"

void APP_Run(void) {
  uint8_t res, fw;
  uint32_t sna;
  uint32_t snb;
  SI7021_DeviceID id;
  float t, h;

  /* initialization */
  SI7021_Init();
  SHELL_Init();
#if 1
  res = SI7021_GetSerialBytes(&sna, &snb);
  if (res!=ERR_OK) {
    CLS1_SendStr("Failed SI7021_GetSerialBytes().\r\n", CLS1_GetStdio()->stdErr);
    for(;;){}
  }
  res = SI7021_GetDeviceID(&id);
  if (res!=ERR_OK) {
    CLS1_SendStr("Failed SI7021_GetDeviceID().\r\n", CLS1_GetStdio()->stdErr);
    for(;;){}
  }
  res = SI7021_GetFirmware(&fw);
  if (res!=ERR_OK) {
    CLS1_SendStr("Failed SI7021_GetFirmware().\r\n", CLS1_GetStdio()->stdErr);
    for(;;){}
  }
  res = SI7021_ReadTemperatureHold(&t);
  if (res!=ERR_OK) {
    CLS1_SendStr("Failed SI7021_ReadTemperature().\r\n", CLS1_GetStdio()->stdErr);
    for(;;){}
  }
  res = SI7021_ReadHumidityHold(&h);
  if (res!=ERR_OK) {
    CLS1_SendStr("Failed SI7021_ReadHumidity().\r\n", CLS1_GetStdio()->stdErr);
    for(;;){}
  }
#endif
  for(;;) {
    LED1_Neg();
    SHELL_Parse();
    WAIT1_Waitms(50);
  }
}
