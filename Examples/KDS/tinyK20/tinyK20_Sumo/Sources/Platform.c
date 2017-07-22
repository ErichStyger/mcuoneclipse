/*
 * Platform.c
 *
 *  Created on: 17.07.2017
 *      Author: Erich Styger Local
 */


#include "Platform.h"
#include "Shell.h"
#include "Motor.h"


void PL_Init(void) {
#if PL_CONFIG_HAS_SHELL
  SHELL_Init();
#endif
#if PL_CONFIG_HAS_MOTOR
  MOT_Init();
#endif
}
