/**
 * \file
 * \brief Accelerometer Module
 * \author Erich Styger, erich.styger@hslu.ch
 * \license SPDX-License-Identifier: BSD-3-Clause
 * Module to interface with the robot FXOS8700 accelerometer and magnetometer.
 */

#include "platform.h" /* interface to the platform */

#if PL_CONFIG_HAS_ACCEL
#include "Accel.h"    /* our own interface */
#include "McuFXOS8700.h"
#include "McuRTOS.h"
#include "McuCriticalSection.h"

#if PL_HAS_FREEMASTER
static int16_t accelX, accelY, accelZ; /* FreeMASTER needs global variables */
#endif

void ACCEL_GetValues(int16_t *x, int16_t *y, int16_t *z) {
  int16_t xmg, ymg, zmg;
  
  xmg = McuFXOS8700_GetXmg();
  ymg = McuFXOS8700_GetYmg();
  zmg = McuFXOS8700_GetZmg();
#if PL_HAS_FREEMASTER
  McuCriticalSection_CriticalVariable()

  McuCriticalSection_EnterCritical();
  accelX = xmg;
  accelY = ymg;
  accelZ = zmg;
  McuCriticalSection_ExitCritical();
#endif
  *x = xmg;
  *y = ymg;
  *z = zmg;
}

void ACCEL_Deinit(void) {
  (void)McuFXOS8700_Deinit();
}

uint8_t ACCEL_LowLevelInit(void) {
  uint8_t res;
  
  res = McuFXOS8700_Init(); /* this might communicate to the device using I2C, so it needs interrupts enabled */
  if (res!=ERR_OK) {
    return res;
  }
#if PL_IS_FRDM
  res = McuFXOS8700_SetFastMode(FALSE); /* disable fast mode of the sensor: otherwise we cannot read individual sensor values */
  if (res!=ERR_OK) {
    return res;
  }
#endif
  return ERR_OK;
}

uint8_t ACCEL_Enable(void) {
  (void)McuFXOS8700_MagEnable();
  return McuFXOS8700_Enable();
}

uint8_t ACCEL_isEnabled(bool *isEnabled) {
  return McuFXOS8700_isEnabled(isEnabled);
}

/*! \brief Initializes module */
void ACCEL_Init(void) {
#if !PL_HAS_RTOS /* with an RTOS, the interrupts are disabled here. Need to do this in a task */
  ACCEL_LowLevelInit();
#endif
}
#endif /* PL_CONFIG_HAS_ACCEL */

