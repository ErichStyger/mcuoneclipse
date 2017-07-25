/**
 * \file
 * \brief Accelerometer Module
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * Module to calculate the speed based on the quadrature counter.
 */

#include "Platform.h" /* interface to the platform */

#if PL_HAS_ACCEL
#include "Accel.h"    /* our own interface */
#include "MMA1.h"
#include "FRTOS1.h"
#include "CS1.h"

#if PL_HAS_FREEMASTER
static int16_t accelX, accelY, accelZ; /* FreeMASTER needs global variables */
#endif

void ACCEL_GetValues(int16_t *x, int16_t *y, int16_t *z) {
  int16_t xmg, ymg, zmg;
  
  xmg = MMA1_GetXmg();
  ymg = MMA1_GetYmg();
  zmg = MMA1_GetZmg();
#if PL_HAS_FREEMASTER
  CS1_EnterCritical();
  accelX = xmg;
  accelY = ymg;
  accelZ = zmg;
  CS1_ExitCritical();
#endif
  *x = xmg;
  *y = ymg;
  *z = zmg;
}

void ACCEL_Deinit(void) {
  (void)MMA1_Deinit();
}

uint8_t ACCEL_LowLevelInit(void) {
  uint8_t res;
  
  res = MMA1_Init(); /* this might communicate to the device using I2C, so it needs interrupts enabled */
  if (res!=ERR_OK) {
    return res;
  }
#if PL_IS_FRDM
  res = MMA1_SetFastMode(FALSE); /* disable fast mode of the sensor: otherwise we cannot read individual sensor values */
  if (res!=ERR_OK) {
    return res;
  }
#endif
  return ERR_OK;
}

uint8_t ACCEL_Enable(void) {
  uint8_t res;
  
  res = MMA1_Enable();
  return res;
}

uint8_t ACCEL_isEnabled(bool *isEnabled) {
  uint8_t res;
  
  res = MMA1_isEnabled(isEnabled);
  return res;
}

/*! \brief Initializes module */
void ACCEL_Init(void) {
#if !PL_HAS_RTOS /* with an RTOS, the interrupts are disabled here. Need to do this in a task */
  ACCEL_LowLevelInit();
#endif
}
#endif /* PL_HAS_ACCEL */

