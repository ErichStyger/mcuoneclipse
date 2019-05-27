/*
 * McuButton.h
 *
 *  Created on: 27.05.2019
 *      Author: Erich Styger
 */

#ifndef MCUBUTTON_H_
#define MCUBUTTON_H_

#include <stdint.h>
#include <stdbool.h>
#include "McuLib.h"
#include "fsl_gpio.h"


typedef void *McuBtn_Handle_t;

typedef struct {
#if McuLib_CONFIG_CPU_IS_KINETIS
  PORT_Type *port;
#elif McuLib_CONFIG_CPU_IS_LPC
  uint32_t port;
#endif
  uint32_t pin;
} McuBtn_Config_t;

void McuBtn_GetDefaultConfig(McuBtn_Config_t *config);

McuBtn_Handle_t McuBtn_InitLed(McuBtn_Config_t *config);

McuBtn_Handle_t McuBtn_DeinitLed(McuBtn_Handle_t led);

void McuBtn_Deinit(void);

void McuBtn_Init(void);

#endif /* MCUBUTTON_H_ */
