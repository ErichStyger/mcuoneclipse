/*
 * Copyright (c) 2019, Erich Styger
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "McuULN2003config.h"
#include "McuULN2003.h"
#include "McuGPIO.h"
#include "McuWait.h"
#if McuLib_CONFIG_CPU_IS_KINETIS
  #include "fsl_port.h"
#endif
#if MCUULN2003_CONFIG_USE_FREERTOS_HEAP
  #include "McuRTOS.h"
#endif

#if McuULN2003_CONFIG_USE_ACCELERATION
static const uint8_t default_accel_delays[] = {2, 2, 2, 2, 2, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 6, 6, 6, 8, 8, 10, 10, 10};
static const McuULN2003_Accel_t McuULN2003_DefaultAccelTable =
{ /* list of delay values: the larger the value, the more delays between the step sequences. */
  .nofEntries = sizeof(default_accel_delays),
  .delays = default_accel_delays,
};
#endif

typedef struct {
  int32_t pos; /* actual stepper motor position counter */
  McuULN2003_StepMode stepMode; /* full or half stepping mode */
  bool inverted; /* if motor direction is inverted */
  uint8_t tablePos; /* current pos in the stepper logic table */
#if McuULN2003_CONFIG_USE_ACCELERATION
  struct {
    const McuULN2003_Accel_t *table;
    uint8_t accelIdx; /* current index into acceleration delay table, starting from the end of the table to index zero */
    uint8_t subAccelCnt; /* sub-position acceleration counter, used to count down the delay */
  } accel;
#endif
  McuGPIO_Handle_t pin[McuULN2003_NOF_MOTOR_GPIO_PINS]; /* the 4 winding of the motor */
} McuULN2003_Motor_t;

#define McuULN2003_NOF_STEPS_HALF_STEP_MODE    (8)
#define McuULN2003_DELAY_HALF_STEP_MODE()      McuWait_WaitOSms(2)

#define McuULN2003_NOF_STEPS_FULL_STEP_MODE    (4)
#define McuULN2003_DELAY_FULL_STEP_MODE()      McuWait_WaitOSms(4)

typedef bool McuULN2003_PinStatus[McuULN2003_NOF_MOTOR_GPIO_PINS];

static const bool disableTable[McuULN2003_NOF_MOTOR_GPIO_PINS] = { false, false, false, false};

/* half stepping mode with 8 steps */
static const bool stepTableHalfStepsFw[McuULN2003_NOF_STEPS_HALF_STEP_MODE][McuULN2003_NOF_MOTOR_GPIO_PINS] = {
    {true,  false, false, false},
    {true,  true,  false, false},
    {false, true,  false, false},
    {false, true,  true,  false},
    {false, false, true,  false},
    {false, false, true,  true },
    {false, false, false, true },
    {true,  false, false, true },
};
static const bool stepTableHalfStepsBw[McuULN2003_NOF_STEPS_HALF_STEP_MODE][McuULN2003_NOF_MOTOR_GPIO_PINS] = {
    {true,  false, false, true },
    {false, false, false, true },
    {false, false, true,  true },
    {false, false, true,  false},
    {false, true,  true,  false},
    {false, true,  false, false},
    {true,  true,  false, false},
    {true,  false, false, false},
};

/* full stepping mode with 4 steps */
static const bool stepTableFullStepsFw[McuULN2003_NOF_STEPS_FULL_STEP_MODE][McuULN2003_NOF_MOTOR_GPIO_PINS] = {
    {true,  false, false, false},
    {false, true,  false, false},
    {false, false, true,  false},
    {false, false, false, true },
};
static const bool stepTableFullStepsBw[McuULN2003_NOF_STEPS_FULL_STEP_MODE][McuULN2003_NOF_MOTOR_GPIO_PINS] = {
    {false, false, false, true },
    {false, false, true,  false},
    {false, true,  false, false},
    {true,  false, false, false},
};

/* default configuration, used for initializing the config */
static const McuULN2003_Config_t defaultConfig =
{
    .stepMode = McuULN2003_STEP_MODE_HALF,
    .inverted = false,
    .hw[0] = {
      .gpio = NULL,
  #if McuLib_CONFIG_CPU_IS_KINETIS
      .port = NULL,
  #elif McuLib_CONFIG_CPU_IS_LPC
      .port = 0,
  #endif
      .pin = 0,
    },
    .hw[1] = {
      .gpio = NULL,
  #if McuLib_CONFIG_CPU_IS_KINETIS
      .port = NULL,
  #elif McuLib_CONFIG_CPU_IS_LPC
      .port = 0,
  #endif
      .pin = 0,
    },
    .hw[2] = {
      .gpio = NULL,
  #if McuLib_CONFIG_CPU_IS_KINETIS
      .port = NULL,
  #elif McuLib_CONFIG_CPU_IS_LPC
      .port = 0,
  #endif
      .pin = 0,
    },
    .hw[3] = {
      .gpio = NULL,
  #if McuLib_CONFIG_CPU_IS_KINETIS
      .port = NULL,
  #elif McuLib_CONFIG_CPU_IS_LPC
      .port = 0,
  #endif
      .pin = 0,
    }
};

void McuULN2003_GetDefaultConfig(McuULN2003_Config_t *config) {
  assert(config!=NULL);
  memcpy(config, &defaultConfig, sizeof(*config));
}

#if McuULN2003_CONFIG_USE_ACCELERATION
void McuULN2003_SetAccelerationTable(McuULN2003_Handle_t motor, const McuULN2003_Accel_t *table) {
  McuULN2003_Motor_t *handle;

  handle = (McuULN2003_Motor_t*)motor;
  handle->accel.table = table;
  handle->accel.accelIdx = 0;
  handle->accel.subAccelCnt = 0;
}
#endif

McuULN2003_Handle_t McuULN2003_InitMotor(McuULN2003_Config_t *config) {
  McuGPIO_Config_t gpio_config; /* config for the SDK */
  McuULN2003_Motor_t *handle;

  assert(config!=NULL);
#if MCUULN2003_CONFIG_USE_FREERTOS_HEAP
  handle = (McuULN2003_Motor_t*)pvPortMalloc(sizeof(McuULN2003_Motor_t)); /* get a new device descriptor */
#else
  handle = (McuULN2003_Motor_t*)malloc(sizeof(McuULN2003_Motor_t)); /* get a new device descriptor */
#endif
  assert(handle!=NULL);
  if (handle!=NULL) { /* if malloc failed, will return NULL pointer */
    memset(handle, 0, sizeof(McuULN2003_Motor_t)); /* init all fields */
#if McuULN2003_CONFIG_USE_ACCELERATION
    McuULN2003_SetAccelerationTable((McuULN2003_Handle_t*)handle, &McuULN2003_DefaultAccelTable);
#endif
    handle->pos = 0;
    handle->stepMode = config->stepMode;
    handle->inverted = config->inverted;
    handle->tablePos = 0;
    McuGPIO_GetDefaultConfig(&gpio_config);
    for(int i=0; i<McuULN2003_NOF_MOTOR_GPIO_PINS; i++) {
      gpio_config.isInput = false; /* motor pin is output only */
      gpio_config.hw.gpio = config->hw[i].gpio;
    #if McuLib_CONFIG_CPU_IS_KINETIS || McuLib_CONFIG_CPU_IS_LPC
      gpio_config.hw.port = config->hw[i].port;
    #endif
      gpio_config.hw.pin  = config->hw[i].pin;
      gpio_config.isHighOnInit = false;
      handle->pin[i] = McuGPIO_InitGPIO(&gpio_config); /* create gpio handle */
    }
  }
  return handle;
}

McuULN2003_Handle_t McuULN2003_DeinitMotor(McuULN2003_Handle_t motor) {
  McuULN2003_Motor_t *m = (McuULN2003_Motor_t*)motor;
  assert(m!=NULL);

  for(int i=0; i<McuULN2003_NOF_MOTOR_GPIO_PINS; i++) {
    McuGPIO_DeinitGPIO(m->pin[i]);
  }
#if MCUULN2003_CONFIG_USE_FREERTOS_HEAP
  vPortFree(m);
#else
  free(m);
#endif
  return NULL;
}

void McuULN2003_SetStepMode(McuULN2003_Handle_t motor, McuULN2003_StepMode mode) {
  ((McuULN2003_Motor_t*)motor)->stepMode = mode;
}

McuULN2003_StepMode McuULN2003_GetStepMode(McuULN2003_Handle_t motor) {
  return ((McuULN2003_Motor_t*)motor)->stepMode;
}

static void SetStep(McuULN2003_Motor_t *motor, const bool w[McuULN2003_NOF_MOTOR_GPIO_PINS]) {
  for(int i=0; i<McuULN2003_NOF_MOTOR_GPIO_PINS; i++) { /* for all pins */
    McuGPIO_SetValue(motor->pin[i], w[i]);
  }
}

void McuULN2003_PowerOff(McuULN2003_Handle_t motor) {
  SetStep((McuULN2003_Motor_t *)motor, disableTable);
  ((McuULN2003_Motor_t *)motor)->tablePos = 0;
}

static void McuULN2003_TableMakeStep(McuULN2003_Handle_t motor, bool forward) {
  McuULN2003_Motor_t *m = (McuULN2003_Motor_t*)motor;
  const McuULN2003_PinStatus *table;
  size_t maxTableIndex;

  if (m->stepMode==McuULN2003_STEP_MODE_HALF) {
    if ((forward && !m->inverted) || (!forward && m->inverted)) {
      table = stepTableHalfStepsFw;
    } else {
      table = stepTableHalfStepsBw;
    }
    maxTableIndex = McuULN2003_NOF_STEPS_HALF_STEP_MODE;
  } else { /* McuULN2003_STEP_MODE_FULL */
    if ((forward && !m->inverted) || (!forward && m->inverted)) {
      table = stepTableFullStepsFw;
    } else {
      table = stepTableFullStepsBw;
    }
    maxTableIndex = McuULN2003_NOF_STEPS_FULL_STEP_MODE;
  }
  SetStep(m, table[m->tablePos]);
  m->tablePos++;
  if (m->tablePos>=maxTableIndex) { /* full sequence reached */
    m->tablePos = 0;
    if (forward) {
      m->pos++;
    } else {
      m->pos--;
    }
  }
}

bool McuULN2003_StepCallback(McuULN2003_Handle_t motor, bool forward) {
  McuULN2003_Motor_t *m = (McuULN2003_Motor_t*)motor;

#if McuULN2003_CONFIG_USE_ACCELERATION
  if (m->accel.accelIdx>0) { /* only do it if not during acceleration */
    if (m->accel.subAccelCnt>0) { /* sub-delay still going on? */
      m->accel.subAccelCnt--; /* delay */
      return false; /* not reached end of delay sequence */
    } else { /* subAccelCnt reached zero: get to next table index value */
      m->accel.accelIdx--;
      m->accel.subAccelCnt = m->accel.table->delays[m->accel.accelIdx];
    }
  }
#endif
  if (forward) {
    McuULN2003_TableMakeStep(motor, true); /* forward */
  } else {
    McuULN2003_TableMakeStep(motor, false); /* backward */
  }
  return m->tablePos==0; /* reached position */
}

#if McuULN2003_CONFIG_USE_ACCELERATION
void McuULN2003_AccelerationStart(McuULN2003_Handle_t motor) {
  McuULN2003_Motor_t *m = (McuULN2003_Motor_t*)motor;
  m->accel.accelIdx = m->accel.table->nofEntries-1;
  m->accel.subAccelCnt = m->accel.table->delays[m->accel.table->nofEntries-1];
}
#endif

#if McuULN2003_CONFIG_USE_ACCELERATION
void McuULN2003_AccelerationEnd(McuULN2003_Handle_t motor) {
  McuULN2003_Motor_t *m = (McuULN2003_Motor_t*)motor;
  m->accel.accelIdx = 0;
  m->accel.subAccelCnt = 0;
}
#endif

bool McuULN2003_MoveCallback(McuULN2003_Handle_t motor, int32_t targetPos) {
  McuULN2003_Motor_t *m = (McuULN2003_Motor_t*)motor;

  if (m->pos < targetPos) {
    McuULN2003_TableMakeStep(motor, true); /* forward */
    return false;
  } else if (m->pos > targetPos) {
    McuULN2003_TableMakeStep(motor, false); /* backward */
    return false;
  }
  McuULN2003_PowerOff(motor);
  return true; /* reached position */
}

void McuULN2003_IncStep(McuULN2003_Handle_t motor) {
  McuULN2003_Motor_t *m = (McuULN2003_Motor_t*)motor;
  int32_t pos = m->pos+1;

  do {
    McuULN2003_TableMakeStep(motor, true);
    if (m->stepMode==McuULN2003_STEP_MODE_HALF) {
      McuULN2003_DELAY_HALF_STEP_MODE();
    } else { /* McuULN2003_STEP_MODE_FULL */
      McuULN2003_DELAY_FULL_STEP_MODE();
    }
  } while(m->pos!=pos);
}

void McuULN2003_DecStep(McuULN2003_Handle_t motor) {
  McuULN2003_Motor_t *m = (McuULN2003_Motor_t*)motor;
  int32_t pos = m->pos-1;

  do {
    McuULN2003_TableMakeStep(motor, false);
    if (m->stepMode==McuULN2003_STEP_MODE_HALF) {
      McuULN2003_DELAY_HALF_STEP_MODE();
    } else { /* McuULN2003_STEP_MODE_FULL */
      McuULN2003_DELAY_FULL_STEP_MODE();
    }
  } while(m->pos!=pos);
}

void McuULN2003_SetPos(McuULN2003_Handle_t motor, int32_t pos) {
  McuULN2003_Motor_t *m = (McuULN2003_Motor_t*)motor;
  m->pos = pos;
}

int32_t McuULN2003_GetPos(McuULN2003_Handle_t motor) {
  return ((McuULN2003_Motor_t*)motor)->pos;
}

void McuULN2003_Step(McuULN2003_Handle_t motor, int32_t steps) {
  if (steps>0) {
    while(steps>0) {
      McuULN2003_IncStep(motor);
      steps--;
    }
  } else {
    while(steps<0) {
      McuULN2003_DecStep(motor);
      steps++;
    }
  }
}

void McuULN2003_Deinit(void) {
  /* nothing needed */
}

void McuULN2003_Init(void) {
  /* nothing needed */
}
