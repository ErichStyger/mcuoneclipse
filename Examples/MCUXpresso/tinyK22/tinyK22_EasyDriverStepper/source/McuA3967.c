/*
 * Copyright (c) 2019, Erich Styger
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "McuA3967config.h"
#include "McuA3967.h"
#include "McuGPIO.h"
#include "McuWait.h"
#include "McuUtility.h"
#include <assert.h>
#include <string.h> /* for memset */
#include <stdlib.h> /* for malloc() and free() */
#if MCUA3967_CONFIG_USE_FREERTOS_HEAP
  #include "McuRTOS.h"
#endif

/* default configuration, used for initializing the config */
static const McuA3967_Config_t defaultConfig =
{
  .rst = { /* reset pin */
      .gpio = NULL,
    #if McuLib_CONFIG_CPU_IS_KINETIS
      .port = NULL,
    #elif McuLib_CONFIG_CPU_IS_LPC
      .port = 0,
    #endif
      .pin = 0,
  },
  .enable = { /* reset pin */
      .gpio = NULL,
    #if McuLib_CONFIG_CPU_IS_KINETIS
      .port = NULL,
    #elif McuLib_CONFIG_CPU_IS_LPC
      .port = 0,
    #endif
      .pin = 0,
  },
  .slp = { /* reset pin */
      .gpio = NULL,
    #if McuLib_CONFIG_CPU_IS_KINETIS
      .port = NULL,
    #elif McuLib_CONFIG_CPU_IS_LPC
      .port = 0,
    #endif
      .pin = 0,
  },
  .ms1 = { /* reset pin */
      .gpio = NULL,
    #if McuLib_CONFIG_CPU_IS_KINETIS
      .port = NULL,
    #elif McuLib_CONFIG_CPU_IS_LPC
      .port = 0,
    #endif
      .pin = 0,
  },
  .ms2 = { /* reset pin */
      .gpio = NULL,
    #if McuLib_CONFIG_CPU_IS_KINETIS
      .port = NULL,
    #elif McuLib_CONFIG_CPU_IS_LPC
      .port = 0,
    #endif
      .pin = 0,
  },
  .step = { /* reset pin */
      .gpio = NULL,
    #if McuLib_CONFIG_CPU_IS_KINETIS
      .port = NULL,
    #elif McuLib_CONFIG_CPU_IS_LPC
      .port = 0,
    #endif
      .pin = 0,
  },
  .dir = { /* reset pin */
      .gpio = NULL,
    #if McuLib_CONFIG_CPU_IS_KINETIS
      .port = NULL,
    #elif McuLib_CONFIG_CPU_IS_LPC
      .port = 0,
    #endif
      .pin = 0,
  }
};

typedef struct {
  int32_t pos; /* current position */
  McuGPIO_Handle_t reset;     /* reset pin, low active  */
  McuGPIO_Handle_t enable;    /* enable pin, low active */
  McuGPIO_Handle_t ms1, ms2;  /* configures micro stepping */
  McuGPIO_Handle_t sleep;     /* sleep pin, low active */
  McuGPIO_Handle_t step;      /* step pin, low->high does a step */
  McuGPIO_Handle_t dir;       /* direction pin */
} McuA3967_Stepper_t;

bool McuA3967_GetReset(McuA3967_Handle_t stepper) {
  return McuGPIO_IsLow(((McuA3967_Stepper_t*)stepper)->reset);
}

void McuA3967_SetReset(McuA3967_Handle_t stepper, bool reset) {
  McuGPIO_SetValue(((McuA3967_Stepper_t*)stepper)->reset, !reset); /* reset is low active */
}

bool McuA3967_GetEnable(McuA3967_Handle_t stepper) {
  /* LOW: enabled, HIGH: disabled */
  return McuGPIO_IsLow(((McuA3967_Stepper_t*)stepper)->enable);
}

void McuA3967_SetEnable(McuA3967_Handle_t stepper, bool enable) {
  /* LOW: enabled, HIGH: disabled */
  McuGPIO_SetValue(((McuA3967_Stepper_t*)stepper)->enable, !enable); /* enable is low active */
}

bool McuA3967_GetDirection(McuA3967_Handle_t stepper) {
  return McuGPIO_IsHigh(((McuA3967_Stepper_t*)stepper)->dir);
}

void McuA3967_SetDirection(McuA3967_Handle_t stepper, bool forward) {
  McuGPIO_SetValue(((McuA3967_Stepper_t*)stepper)->dir, forward);
}

bool McuA3967_GetSleep(McuA3967_Handle_t stepper) {
  return McuGPIO_IsLow(((McuA3967_Stepper_t*)stepper)->sleep); /* sleep is low active */
}

void McuA3967_SetSleep(McuA3967_Handle_t stepper, bool sleep) {
  McuGPIO_SetValue(((McuA3967_Stepper_t*)stepper)->sleep, !sleep); /* sleep is low active */
}

uint8_t McuA3967_GetMicroStepping(McuA3967_Handle_t stepper) {
  uint8_t ms12;

  ms12 = McuGPIO_IsHigh(((McuA3967_Stepper_t*)stepper)->ms1)?2:0;
  ms12 |= McuGPIO_IsHigh(((McuA3967_Stepper_t*)stepper)->ms2)?1:0;
  switch(ms12) {
    default:
    case 0: return 1;
    case 2: return 2;
    case 1: return 4;
    case 3: return 8;
  }
}

void McuA3967_SetMicroStepping(McuA3967_Handle_t stepper, uint8_t mode) {
  switch(mode) {
    default:
    case 1:
      McuGPIO_SetLow(((McuA3967_Stepper_t*)stepper)->ms1);
      McuGPIO_SetLow(((McuA3967_Stepper_t*)stepper)->ms2);
      break;
    case 2:
      McuGPIO_SetHigh(((McuA3967_Stepper_t*)stepper)->ms1);
      McuGPIO_SetLow(((McuA3967_Stepper_t*)stepper)->ms2);
      break;
    case 4:
      McuGPIO_SetLow(((McuA3967_Stepper_t*)stepper)->ms1);
      McuGPIO_SetHigh(((McuA3967_Stepper_t*)stepper)->ms2);
      break;
    case 8:
      McuGPIO_SetHigh(((McuA3967_Stepper_t*)stepper)->ms1);
      McuGPIO_SetHigh(((McuA3967_Stepper_t*)stepper)->ms2);
      break;
  }
}

bool McuA3967_GetStep(McuA3967_Handle_t stepper) {
  return McuGPIO_IsHigh(((McuA3967_Stepper_t*)stepper)->step);
}

void McuA3967_SetStep(McuA3967_Handle_t stepper, bool status) {
  McuGPIO_SetValue(((McuA3967_Stepper_t*)stepper)->step, status);
}

void McuA3967_MakeStep(McuA3967_Handle_t stepper) {
  McuA3967_Stepper_t *motor = (McuA3967_Stepper_t*)stepper;

  McuGPIO_SetHigh(motor->step);
  McuWait_Waitus(1);
  McuGPIO_SetLow(motor->step);
  McuWait_Waitus(1);
}

void McuA3967_GetDefaultConfig(McuA3967_Config_t *config) {
  assert(config!=NULL);
  memcpy(config, &defaultConfig, sizeof(*config));
}

McuA3967_Handle_t McuA3967_InitHandle(McuA3967_Config_t *config) {
  McuGPIO_Config_t gpio_config; /* config for the SDK */
  McuGPIO_Handle_t gpio;
  McuA3967_Stepper_t *handle;

  assert(config!=NULL);
#if MCUA3967_CONFIG_USE_FREERTOS_HEAP
  handle = (McuA3967_Stepper_t*)pvPortMalloc(sizeof(McuA3967_Stepper_t)); /* get a new device descriptor */
#else
  handle = (McuA3967_Stepper_t*)malloc(sizeof(McuA3967_Stepper_t)); /* get a new device descriptor */
#endif
  assert(handle!=NULL);
  if (handle==NULL) {
    return NULL; /* error case */
  }
  memset(handle, 0, sizeof(McuA3967_Stepper_t)); /* init all fields */

  /* reset pin */
  McuGPIO_GetDefaultConfig(&gpio_config);
  gpio_config.isInput = false; /* reset it output only */
  gpio_config.isHighOnInit = false; /* pin is LOW active, have it disabled (LOW) initially */
  gpio_config.hw.gpio = config->rst.gpio;
  gpio_config.hw.port = config->rst.port;
  gpio_config.hw.pin  = config->rst.pin;
  gpio = McuGPIO_InitGPIO(&gpio_config); /* create gpio handle */
  handle->reset = gpio;

  /* enable pin */
  McuGPIO_GetDefaultConfig(&gpio_config);
  gpio_config.isInput = false; /* enable it output only */
  gpio_config.isHighOnInit = true; /* pin is LOW active, have it disabled initially => HIGH */
  gpio_config.hw.gpio = config->enable.gpio;
  gpio_config.hw.port = config->enable.port;
  gpio_config.hw.pin  = config->enable.pin;
  gpio = McuGPIO_InitGPIO(&gpio_config); /* create gpio handle */
  handle->enable = gpio;

  /* sleep pin */
  McuGPIO_GetDefaultConfig(&gpio_config);
  gpio_config.isInput = false; /* sleep it output only */
  gpio_config.isHighOnInit = false; /* pin is LOW active, have it disabled initially */
  gpio_config.hw.gpio = config->slp.gpio;
  gpio_config.hw.port = config->slp.port;
  gpio_config.hw.pin  = config->slp.pin;
  gpio = McuGPIO_InitGPIO(&gpio_config); /* create gpio handle */
  handle->sleep = gpio;

  /* ms1 pin */
  McuGPIO_GetDefaultConfig(&gpio_config);
  gpio_config.isInput = false; /* ms1 it output only */
  gpio_config.isHighOnInit = false; /* initial setting for full stepping */
  gpio_config.hw.gpio = config->ms1.gpio;
  gpio_config.hw.port = config->ms1.port;
  gpio_config.hw.pin  = config->ms1.pin;
  gpio = McuGPIO_InitGPIO(&gpio_config); /* create gpio handle */
  handle->ms1 = gpio;

  /* ms2 pin */
  McuGPIO_GetDefaultConfig(&gpio_config);
  gpio_config.isInput = false; /* ms1 it output only */
  gpio_config.isHighOnInit = false; /* initial setting for full stepping */
  gpio_config.hw.gpio = config->ms2.gpio;
  gpio_config.hw.port = config->ms2.port;
  gpio_config.hw.pin  = config->ms2.pin;
  gpio = McuGPIO_InitGPIO(&gpio_config); /* create gpio handle */
  handle->ms2 = gpio;

  /* step pin */
  McuGPIO_GetDefaultConfig(&gpio_config);
  gpio_config.isInput = false; /* step it output only */
  gpio_config.isHighOnInit = false; /* initially low */
  gpio_config.hw.gpio = config->step.gpio;
  gpio_config.hw.port = config->step.port;
  gpio_config.hw.pin  = config->step.pin;
  gpio = McuGPIO_InitGPIO(&gpio_config); /* create gpio handle */
  handle->step = gpio;

  /* direction pin */
  McuGPIO_GetDefaultConfig(&gpio_config);
  gpio_config.isInput = false; /* direction it output only */
  gpio_config.isHighOnInit = false; /* initially low */
  gpio_config.hw.gpio = config->dir.gpio;
  gpio_config.hw.port = config->dir.port;
  gpio_config.hw.pin  = config->dir.pin;
  gpio = McuGPIO_InitGPIO(&gpio_config); /* create gpio handle */
  handle->dir = gpio;

  return (McuA3967_Handle_t)handle;
}

#if McuA3967_CONFIG_PARSE_COMMAND_ENABLED
static uint8_t PrintStatus(const McuShell_StdIOType *io) {
  McuShell_SendStatusStr((unsigned char*)"A3967", (unsigned char*)"\r\n", io->stdOut);
  McuShell_SendStatusStr((unsigned char*)"  tbd", (unsigned char*)"\r\n", io->stdOut);
  return ERR_OK;
}

uint8_t McuA3967_PrintStepperStatus(McuA3967_Handle_t stepper, const unsigned char *name, const McuShell_StdIOType *io) {
  uint8_t buf[24];

  McuShell_SendStatusStr(name, (unsigned char*)"\r\n", io->stdOut);
  McuShell_SendStatusStr((unsigned char*)"  RESET", McuA3967_GetReset(stepper)?(unsigned char*)"yes (LOW)\r\n":(unsigned char*)"no (HIGH)\r\n", io->stdOut);
  McuShell_SendStatusStr((unsigned char*)"  DIR", McuA3967_GetDirection(stepper)?(unsigned char*)"forward (HIGH)\r\n":(unsigned char*)"backward (LOW)\r\n", io->stdOut);
  McuShell_SendStatusStr((unsigned char*)"  SLP", McuA3967_GetSleep(stepper)?(unsigned char*)"yes (LOW)\r\n":(unsigned char*)"no (HIGH)\r\n", io->stdOut);
  McuShell_SendStatusStr((unsigned char*)"  ENABLE", McuA3967_GetEnable(stepper)?(unsigned char*)"yes (LOW)\r\n":(unsigned char*)"no (HIGH)\r\n", io->stdOut);
  McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"1/");
  McuUtility_strcatNum8u(buf, sizeof(buf), McuA3967_GetMicroStepping(stepper));
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" micro step\r\n");
  McuShell_SendStatusStr((unsigned char*)"  MS1,MS2", buf, io->stdOut);
  McuShell_SendStatusStr((unsigned char*)"  STEP", McuA3967_GetStep(stepper)?(unsigned char*)"HIGH\r\n":(unsigned char*)"LOW\r\n", io->stdOut);
  return ERR_OK;
}

static uint8_t PrintHelp(const McuShell_StdIOType *io) {
  McuShell_SendHelpStr((unsigned char*)"A3967", (unsigned char*)"Group of A3967 commands\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  help|status", (unsigned char*)"Print help or status information\r\n", io->stdOut);
  return ERR_OK;
}

uint8_t McuA3967_ParseCommand(const unsigned char* cmd, bool *handled, const McuShell_StdIOType *io) {
  uint8_t res = ERR_OK;

  if (McuUtility_strcmp((char*)cmd, McuShell_CMD_HELP) == 0
    || McuUtility_strcmp((char*)cmd, "A3967 help") == 0) {
    *handled = TRUE;
    return PrintHelp(io);
  } else if (   (McuUtility_strcmp((char*)cmd, McuShell_CMD_STATUS)==0)
             || (McuUtility_strcmp((char*)cmd, "A3967 status") == 0)
            )
  {
    *handled = TRUE;
    res = PrintStatus(io);
#if 0
  } else if (McuUtility_strcmp((char*)cmd, "McuArmTools reset") == 0) {
    *handled = TRUE;
    McuArmTools_SoftwareReset(); /* will perform RESET and does NOT return here! */
#endif
  }
  return res;
}
#endif /* McuA3967_CONFIG_PARSE_COMMAND_ENABLED */

McuA3967_Handle_t McuA3967_DeinitHandle(McuA3967_Handle_t stepper){
  assert(stepper!=NULL);
  McuGPIO_DeinitGPIO(((McuA3967_Stepper_t*)stepper)->reset);
#if MCUA3967_CONFIG_USE_FREERTOS_HEAP
  vPortFree(stepper);
#else
  free(stepper);
#endif
  return NULL;
}

void McuA3967_Deinit(void) {
  /* nothing to do */
}

void McuA3967_Init(void){
  /* nothing to do */
}
