/*
 * McuULN2003.h
 *
 *  Created on: 31.07.2019
 *      Author: Erich Styger
 */

#ifndef MCUULN2003_H_
#define MCUULN2003_H_

#include "McuGPIO.h"

typedef void *McuULN2003_Handle_t;

#define McuULN2003_NOF_MOTOR_GPIO_PINS  (4)

typedef struct {
  McuGPIO_HwPin_t hw[McuULN2003_NOF_MOTOR_GPIO_PINS];
} McuULN2003_Config_t;

void McuULN2003_GetDefaultConfig(McuULN2003_Config_t *config);
McuULN2003_Handle_t McuULN2003_InitMotor(McuULN2003_Config_t *config);
McuULN2003_Handle_t McuULN2003_DeinitMotor(McuULN2003_Handle_t motor);

void McuULN2003_Deinit(void);
void McuULN2003_Init(void);

#endif /* MCUULN2003_H_ */
