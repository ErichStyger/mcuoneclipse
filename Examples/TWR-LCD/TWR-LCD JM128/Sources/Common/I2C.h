/** ###################################################################
**     Filename  : I2C.H
**     Project   : TWR_LCD_JM128
**     Processor : MCF51JM128VLH
**     Compiler  : CodeWarrior ColdFireV1 C Compiler
**     Date/Time : 06.02.2010, 12:17
**     Contents  :
**         User source code
**
** ###################################################################*/

#ifndef __I2C_H
#define __I2C_H

/* MODULE I2C */
#include "PE_Types.h"
#include "Platform.h"

/* accelerometer */
int16_t I2C_GetAccelX(void);
int16_t I2C_GetAccelY(void);
int16_t I2C_GetAccelZ(void);

#if PL_HAS_RUNNER
/* runner */
  #define I2C_RUNNER_I2C_MSG_SIZE  128

  uint8_t I2C_GetRunnerMessage(char *buf, size_t bufSize);
#endif

/* motor */
int32_t I2C_GetMotorSpeed(void);
int32_t I2C_GetPIDSpeed(void);

void I2C_OnReceiveData(void);

void I2C_OnSendData(void);

void I2C_HandleEvent(byte event);

void I2C_ClearBuffers(void);

void I2C_SendCmd(void);

void I2C_Init(void);

/* END I2C */

#endif

