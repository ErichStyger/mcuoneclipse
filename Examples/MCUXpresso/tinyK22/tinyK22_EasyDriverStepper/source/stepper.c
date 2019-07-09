/*
 * Copyright (c) 2019, Erich Styger
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "Stepper.h"
#include "McuA3967.h"
#include "McuWait.h"

#define DO_UINT_TEST  (0)

#define PINS_STEPPER1_RST_GPIO      GPIOB
#define PINS_STEPPER1_RST_PORT      PORTB
#define PINS_STEPPER1_RST_PIN       0U

#define PINS_STEPPER1_ENABLE_GPIO   GPIOB
#define PINS_STEPPER1_ENABLE_PORT   PORTB
#define PINS_STEPPER1_ENABLE_PIN    1U

#define PINS_STEPPER1_MS2_GPIO      GPIOB
#define PINS_STEPPER1_MS2_PORT      PORTB
#define PINS_STEPPER1_MS2_PIN       2U

#define PINS_STEPPER1_SLEEP_GPIO    GPIOB
#define PINS_STEPPER1_SLEEP_PORT    PORTB
#define PINS_STEPPER1_SLEEP_PIN     3U

#define PINS_STEPPER1_MS1_GPIO      GPIOB
#define PINS_STEPPER1_MS1_PORT      PORTB
#define PINS_STEPPER1_MS1_PIN       16U

#define PINS_STEPPER1_STEP_GPIO     GPIOB
#define PINS_STEPPER1_STEP_PORT     PORTB
#define PINS_STEPPER1_STEP_PIN      17U

#define PINS_STEPPER1_DIR_GPIO      GPIOB
#define PINS_STEPPER1_DIR_PORT      PORTB
#define PINS_STEPPER1_DIR_PIN       18U

static McuA3967_Handle_t stepper;

#if DO_UINT_TEST
static void UnitTest(void) {
  bool inSleep, dir, enable, reset;
  uint8_t micro;

  enable = McuA3967_GetEnable(stepper);
  if (enable) { /* shall not enabled initially */
    for(;;) {} /* error */
  }
  McuA3967_SetEnable(stepper, true);
  enable = McuA3967_GetEnable(stepper);
  if (!enable) { /* should be enabled now */
    for(;;) {} /* error */
  }
  McuA3967_SetEnable(stepper, false); /* disable it again */

  reset = McuA3967_GetReset(stepper);
  if (!reset) { /* shall be in reset initially */
    for(;;) {} /* error */
  }
  McuA3967_SetReset(stepper, false);
  reset = McuA3967_GetReset(stepper);
  if (reset) { /* shall be in reset now */
    for(;;) {} /* error */
  }
  McuA3967_SetReset(stepper, true); /* put back in reset */

  inSleep = McuA3967_GetSleep(stepper);
  if (!inSleep) { /* shall be in sleep */
    for(;;) {} /* error */
  }
  McuA3967_SetSleep(stepper, !inSleep);
  inSleep = McuA3967_GetSleep(stepper);
  if (inSleep) { /* shall be not in sleep now */
    for(;;) {} /* error */
  }
  McuA3967_SetSleep(stepper, true); /* put back in sleep */

  dir = McuA3967_GetDirection(stepper);
  if (dir) { /* initially false */
    for(;;) {} /* error */
  }
  McuA3967_SetDirection(stepper, true);
  dir = McuA3967_GetDirection(stepper);
  if (!dir) { /* must be true now */ /* somehow fails???????? */
    for(;;) {} /* error */
  }

  micro = McuA3967_GetMicroStepping(stepper);
  if (micro!=1) { /* should be in full step initially */
    for(;;) {}
  }
  McuA3967_SetMicroStepping(stepper, 2);
  micro = McuA3967_GetMicroStepping(stepper);
  if (micro!=2) { /* should be in half stepping now */
    for(;;) {}
  }
  McuA3967_SetMicroStepping(stepper, 4);
  micro = McuA3967_GetMicroStepping(stepper);
  if (micro!=4) { /* should be in quarter stepping now */
    for(;;) {}
  }
  McuA3967_SetMicroStepping(stepper, 8);
  micro = McuA3967_GetMicroStepping(stepper);
  if (micro!=8) { /* should be in 1/8 stepping now */
    for(;;) {}
  }

  McuA3967_SetMicroStepping(stepper, 1); /* set back to full step */
  micro = McuA3967_GetMicroStepping(stepper);
  if (micro!=1) { /* should be in half step now */
    for(;;) {}
  }
}
#endif

#if DO_UINT_TEST
static void DoStepping(void) {
  bool forward = true;
  bool wait = true;
  int i;

  McuA3967_SetDirection(stepper, forward);
  for(i=0;i<100;i++) {
    McuA3967_Step(stepper);
    McuWait_Waitms(25);
  }
}
#endif

void STEPPER_Deinit(void){
}

void STEPPER_Init(void) {
  McuA3967_Config_t config;

  CLOCK_EnableClock(kCLOCK_PortB);

  McuA3967_GetDefaultConfig(&config);

  config.rst.gpio = PINS_STEPPER1_RST_GPIO;
  config.rst.port = PINS_STEPPER1_RST_PORT;
  config.rst.pin = PINS_STEPPER1_RST_PIN;

  config.enable.gpio = PINS_STEPPER1_ENABLE_GPIO;
  config.enable.port = PINS_STEPPER1_ENABLE_PORT;
  config.enable.pin = PINS_STEPPER1_ENABLE_PIN;

  config.slp.gpio = PINS_STEPPER1_SLEEP_GPIO;
  config.slp.port = PINS_STEPPER1_SLEEP_PORT;
  config.slp.pin = PINS_STEPPER1_SLEEP_PIN;

  config.ms1.gpio = PINS_STEPPER1_MS1_GPIO;
  config.ms1.port = PINS_STEPPER1_MS1_PORT;
  config.ms1.pin = PINS_STEPPER1_MS1_PIN;

  config.ms2.gpio = PINS_STEPPER1_MS2_GPIO;
  config.ms2.port = PINS_STEPPER1_MS2_PORT;
  config.ms2.pin = PINS_STEPPER1_MS2_PIN;

  config.dir.gpio = PINS_STEPPER1_DIR_GPIO;
  config.dir.port = PINS_STEPPER1_DIR_PORT;
  config.dir.pin = PINS_STEPPER1_DIR_PIN;

  config.step.gpio = PINS_STEPPER1_STEP_GPIO;
  config.step.port = PINS_STEPPER1_STEP_PORT;
  config.step.pin = PINS_STEPPER1_STEP_PIN;

  stepper = McuA3967_InitHandle(&config);

#if DO_UINT_TEST
  UnitTest();
#endif

  /* enable device */
  McuA3967_SetReset(stepper, false); /* take out of reset */
  McuA3967_SetSleep(stepper, false); /* turn off sleep */
  McuA3967_SetEnable(stepper, true); /* enable device */
#if DO_UINT_TEST
  DoStepping();
#endif
}
