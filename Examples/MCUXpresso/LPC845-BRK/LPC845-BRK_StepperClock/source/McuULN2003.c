/*
 * McuULN2003.c
 *
 *  Created on: 31.07.2019
 *      Author: Erich Styger
 */

#include "platform.h"
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

typedef struct {
  int32_t pos;
  McuGPIO_Handle_t pin[4]; /* the 4 winding of the motor */
} McuULN2003_Motor_t;

#define McuULN2003_NOF_STEP_STEPS       (8)

static const bool disableTable[McuULN2003_NOF_MOTOR_GPIO_PINS] = { false, false, false, false};
static const bool stepTable[McuULN2003_NOF_STEP_STEPS][McuULN2003_NOF_MOTOR_GPIO_PINS] = {
    {true,  false, false, false},
    {true,  true,  false, false},
    {false, true,  false, false},
    {false, true,  true,  false},
    {false, false, true,  false},
    {false, false, true,  true },
    {false, false, false, true },
    {true,  false, false, true }
};

/* default configuration, used for initializing the config */
static const McuULN2003_Config_t defaultConfig =
{
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

McuULN2003_Handle_t McuULN2003_InitMotor(McuULN2003_Config_t *config) {
  McuGPIO_Config_t gpio_config; /* config for the SDK */
  McuULN2003_Motor_t *handle;

  assert(config!=NULL);
#if MCULED_CONFIG_USE_FREERTOS_HEAP
  handle = (McuULN2003_Motor_t*)pvPortMalloc(sizeof(McuULN2003_Motor_t)); /* get a new device descriptor */
#else
  handle = (McuULN2003_Motor_t*)malloc(sizeof(McuULN2003_Motor_t)); /* get a new device descriptor */
#endif
  assert(handle!=NULL);
  if (handle!=NULL) { /* if malloc failed, will return NULL pointer */
    memset(handle, 0, sizeof(McuULN2003_Motor_t)); /* init all fields */
    handle->pos = 0;
    McuGPIO_GetDefaultConfig(&gpio_config);
    for(int i=0; i<McuULN2003_NOF_MOTOR_GPIO_PINS; i++) {
      gpio_config.isInput = false; /* motor pin is output only */
      gpio_config.hw.gpio = config->hw[i].gpio;
    #if McuLib_CONFIG_CPU_IS_KINETIS || McuLib_CONFIG_CPU_IS_LPC
      gpio_config.hw.port = config->hw[i].port;
    #endif
      gpio_config.hw.pin  = config->hw[i].pin;
      gpio_config.isLowOnInit = true;
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
#if MCULED_CONFIG_USE_FREERTOS_HEAP
  vPortFree(m);
#else
  free(m);
#endif
  return NULL;
}

static void SetStep(McuULN2003_Motor_t *motor, const bool w[McuULN2003_NOF_MOTOR_GPIO_PINS]) {
  for(int i=0; i<McuULN2003_NOF_MOTOR_GPIO_PINS; i++) { /* for all pins */
    McuGPIO_SetValue(motor->pin[i], w[i]);
  }
}

void McuULN2003_PowerOff(McuULN2003_Handle_t motor) {
  SetStep((McuULN2003_Motor_t *)motor, disableTable);
}

void McuULN2003_IncStep(McuULN2003_Handle_t motor) {
  McuULN2003_Motor_t *m = (McuULN2003_Motor_t*)motor;

  for(int i=0; i<McuULN2003_NOF_STEP_STEPS; i++) {
    SetStep(m, stepTable[i]);
    McuWait_Waitms(1);
  }
  m->pos++;
}

void McuULN2003_DecStep(McuULN2003_Handle_t motor) {
  McuULN2003_Motor_t *m = (McuULN2003_Motor_t*)motor;

  for(int i=McuULN2003_NOF_STEP_STEPS-1; i>=0; i--) {
    SetStep(m, stepTable[i]);
  }
  m->pos--;
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
}

void McuULN2003_Init(void) {
}
