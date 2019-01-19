/*
 * A3967.h
 *
 *  Created on: 18.01.2019
 *      Author: Erich Styger
 */

#include "Platform.h"

#include "A3967.h"
#include "A3967_STEP.h"
#include "A3967_DIR.h"
#include "A3967_ENABLE.h"
#include "A3967_RST.h"
#include "A3967_SLP.h"
#include "WAIT1.h"

#define A3967_NOF_STEPPERS  (1)

typedef struct {
  void (*setPinHigh)(void);
  void (*setPinLow)(void);
} A3967Gpio_t;

typedef struct {
  int32_t pos;
  bool isForward;
  A3967Gpio_t step, dir, rst, enable, slp;
} A3967Device_t;

static void Step0_High(void) { A3967_STEP_SetVal();  }
static void Step0_Low(void) { A3967_STEP_ClrVal();  }
static void Dir0_High(void) { A3967_DIR_SetVal();  }
static void Dir0_Low(void) { A3967_DIR_ClrVal();  }
static void Rst0_High(void) { A3967_RST_SetVal();  }
static void Rst0_Low(void) { A3967_RST_ClrVal();  }
static void Enable0_High(void) { A3967_ENABLE_SetVal();  }
static void Enable0_Low(void) { A3967_ENABLE_ClrVal();  }
static void Slp0_High(void) { A3967_STEP_SetVal();  }
static void Slp0_Low(void) { A3967_STEP_ClrVal();  }

static A3967Device_t steppers[A3967_NOF_STEPPERS];

A3967Device_t *A3967_GetDevice(uint32_t n) {
  if (n>=A3967_NOF_STEPPERS) {
    return NULL;
  }
  return &steppers[n];
}

void A3967_SetDirection(A3967Device_t *dev, bool isForward) {
  if (isForward && !dev->isForward) {
    dev->dir.setPinHigh();
    dev->isForward = TRUE;
  } else if (!isForward && dev->isForward) {
    dev->dir.setPinLow();
    dev->isForward = TRUE;
  }
}

void A3967_MakeStep(A3967Device_t *dev) {
  dev->step.setPinHigh();
  if (dev->isForward) {
    dev->pos++;
  } else {
    dev->pos++;
  }
  WAIT1_Waitms(1);
  dev->step.setPinLow();
}


void A3967_Init(void) {
  A3967_STEP_ClrVal(); /* rising edge will make a step */
  A3967_DIR_SetVal();  /* direction, forward is HIGH */
  A3967_RST_SetVal(); /* This normally high input signal will reset the internal translator and disable all output drivers when pulled low. */
  A3967_ENABLE_ClrVal(); /* This normally low input signal will disable all outputs when pulled high. */
  A3967_SLP_SetVal(); /* This normally high input signal will minimize power consumption by disabling internal circuitry and the output drivers when pulled low. */

  steppers[0].pos = 0;
  steppers[0].isForward = FALSE;
  steppers[0].step.setPinHigh = Step0_High;
  steppers[0].step.setPinLow = Step0_Low;
  steppers[0].dir.setPinHigh = Dir0_High;
  steppers[0].dir.setPinLow = Dir0_Low;
  steppers[0].rst.setPinHigh = Rst0_High;
  steppers[0].rst.setPinLow = Rst0_Low;
  steppers[0].enable.setPinHigh = Enable0_High;
  steppers[0].enable.setPinLow = Enable0_Low;
  steppers[0].slp.setPinHigh = Slp0_High;
  steppers[0].slp.setPinLow = Slp0_Low;
}

