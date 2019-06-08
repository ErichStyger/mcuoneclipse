/*
 * platform.c
 *
 *  Created on: 06.06.2019
 *      Author: Erich Styger Local
 */


#include "platform.h"
/* McuLib modules */
#include "McuLib.h"
#include "McuWait.h"
#include "McuGPIO.h"
#include "McuLED.h"
#include "McuGenericI2C.h"
#include "McuGenericSWI2C.h"
#include "McuHardFault.h"
#include "McuFXOS8700.h"
/* application modules */
#include "leds.h"
#include "i2clib.h"

void PL_Init(void) {
  uint8_t res;

  /* LEDs are on PTA1, PTA2 and PTD5 */
  CLOCK_EnableClock(kCLOCK_PortA);
  CLOCK_EnableClock(kCLOCK_PortD);
  /* I2C is on PTB2, PTB3 (bitbanging for now) */
  CLOCK_EnableClock(kCLOCK_PortB);

  /* initialize McuLib modules */
  McuLib_Init();
  McuWait_Init();
  McuGPIO_Init();
  McuLED_Init();
  McuGenericI2C_Init();
  McuGenericSWI2C_Init();
  res = McuFXOS8700_Init();
  if (res!=ERR_OK) {
    for(;;) {} /* error case */
  }
  McuHardFault_Init();

  /* initialize application modules */
  LEDS_Init();
  I2CLIB_Init();
}
