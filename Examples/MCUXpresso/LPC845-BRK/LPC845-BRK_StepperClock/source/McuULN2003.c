/*
 * McuULN2003.c
 *
 *  Created on: 31.07.2019
 *      Author: Erich Styger Local
 */

#include "McuULN2003.h"
#include "McuGPIO.h"
#include "McuWait.h"

typedef struct {
  int32_t pos;
  McuGPIO_Handle_t pin[4]; /* the 4 windings of the motor */
} McuULN2003_Motor;

typedef McuULN2003_Motor *McuULN2003_MotorHandle;
#define McuULN2003_NOF_MOTOR_GPIO_PINS  (4)
#define McuULN2003_NOF_STEP_STEPS       (4)

static const bool disableTable[McuULN2003_NOF_MOTOR_GPIO_PINS] = { false, false, false, false};
static const bool stepTable[McuULN2003_NOF_STEP_STEPS][McuULN2003_NOF_MOTOR_GPIO_PINS] = {
    {true,  false, true,  false},
    {false, true,  true,  false},
    {false, true,  false, true},
    {true,  false, false, true}
};


static void SetStep(McuULN2003_MotorHandle motor, const bool w[4]) {
  for(int i=0; i<McuULN2003_NOF_MOTOR_GPIO_PINS; i++) { /* for all pins */
    McuGPIO_SetValue(motor->pin[i], w[i]);
  }
}

void Disable(McuULN2003_MotorHandle motor) {
  SetStep(motor, disableTable);
}

void IncStep(McuULN2003_MotorHandle motor) {
  for(int i=0; i<McuULN2003_NOF_STEP_STEPS; i++) {
    SetStep(motor, stepTable[i]);
  }
  motor->pos++;
}

void DecStep(McuULN2003_MotorHandle motor) {
  for(int i=McuULN2003_NOF_STEP_STEPS-1; i>=0; i--) {
    SetStep(motor, stepTable[i]);
  }
  motor->pos--;
}


void forward(uint32_t delayms, uint32_t steps) {
  while(steps>0) {
    for(int i=0; i<4; i++) {

    }
    steps--;
  }
}
