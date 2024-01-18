/*
 * Copyright (c) 2019, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Driver for the X12.017 Quad-Stepper motor driver
 */

#include "McuX12_017config.h"
#include "McuX12_017.h"
#include "McuLib.h"
#include "McuGPIO.h"
#include "McuWait.h"
#include "McuUtility.h"
#if MCUULN2003_CONFIG_USE_FREERTOS_HEAP
  #include "McuRTOS.h"
#else
  #include <stdlib.h> /* for malloc()/free() */
#endif

typedef struct {
  int32_t pos; /* current position */
  bool isForward; /* if current direction is forward */
  bool isInverted; /* if motor direction is inverted */
  McuGPIO_Handle_t dir; /* direction pin, shall be LOW if not used */
  McuGPIO_Handle_t step; /* step pin, shall be LOW if not used */
} X12_Motor_t;

typedef struct { /* descriptor for X12.017 stepper motor driver */
  bool hasReset;
  McuGPIO_Handle_t reset;  /* LOW active, shall be low at power-on */
  X12_Motor_t m[X12_017_NOF_M]; /* each X12.017 can have up to 4 stepper motors */
} McuX12_Device_t;

/* default configuration, used for initializing the config */
static const McuX12_017_Config_t defaultConfig =
{
    .hasReset = false,
    /* reset pin */
    .hw_reset = {
  #if McuLib_CONFIG_NXP_SDK_USED && !McuLib_CONFIG_IS_KINETIS_KE
      .gpio = NULL,
  #elif McuLib_CONFIG_CPU_IS_STM32
      .gpio = NULL,
  #endif
  #if McuLib_CONFIG_CPU_IS_KINETIS
      .port = NULL,
  #elif McuLib_CONFIG_CPU_IS_LPC
      .port = 0,
  #endif
      .pin = 0,
    },

    .motor[X12_017_M0] = {
      .isInverted =  false,
     },

    .motor[X12_017_M1] = {
      .isInverted =  false,
    },

#if McuX12_017_CONFIG_QUAD_DRIVER
    .motor[X12_017_M2] = {
      .isInverted =  false,
    },

    .motor[X12_017_M3] = {
      .isInverted =  false,
    },
#endif
};

void McuX12_017_GetDefaultConfig(McuX12_017_Config_t *config) {
  memcpy(config, &defaultConfig, sizeof(*config));
}

McuX12_017_Handle_t McuX12_017_DeinitDevice(McuX12_017_Handle_t device) {
  McuX12_Device_t *dev = (McuX12_Device_t*)device;

  if (dev->hasReset) {
    McuGPIO_DeinitGPIO(dev->reset);
  }
  for(int i=0; i<4; i++) {
    McuGPIO_DeinitGPIO(dev->m[i].dir);
    McuGPIO_DeinitGPIO(dev->m[i].step);
  }
#if McuX12_017_CONFIG_USE_FREERTOS_HEAP
  vPortFree(dev);
#else
  free(dev);
#endif
  return NULL;
}

McuX12_017_Handle_t McuX12_017_InitDevice(McuX12_017_Config_t *config) {
  McuGPIO_Config_t gpio_config; /* config for the SDK */
  McuX12_Device_t *handle;

#if McuX12_017_CONFIG_USE_FREERTOS_HEAP
  handle = (McuX12_Device_t*)pvPortMalloc(sizeof(McuX12_Device_t)); /* get a new device descriptor */
#else
  handle = (McuX12_Device_t*)malloc(sizeof(McuX12_Device_t)); /* get a new device descriptor */
#endif
  assert(handle!=NULL);
  if (handle!=NULL) { /* if malloc failed, will return NULL pointer */
    memset(handle, 0, sizeof(McuX12_Device_t)); /* init all fields */
    handle->hasReset = config->hasReset;
    McuGPIO_GetDefaultConfig(&gpio_config);
    if (config->hasReset) {  /* reset pin */
      gpio_config.isInput = false; /* reset pin is output only */
      memcpy(&gpio_config.hw, &config->hw_reset, sizeof(gpio_config.hw)); /* copy hardware info */
      gpio_config.isHighOnInit = false; /* driver reset pin is LOW by default */
      handle->reset = McuGPIO_InitGPIO(&gpio_config); /* create gpio handle */
    }
    for(McuX12_017_Motor_e i=0; i<X12_017_NOF_M; i++) {
      /* step pin */
      gpio_config.isInput = false; /* step pin is output only */
      memcpy(&gpio_config.hw, &config->motor[i].hw_step, sizeof(gpio_config.hw)); /* copy hardware info */
      gpio_config.isHighOnInit = false;
      handle->m[i].step = McuGPIO_InitGPIO(&gpio_config); /* create gpio handle */

      /* direction pin */
      handle->m[i].isInverted = config->motor[i].isInverted;
      handle->m[i].isForward = true;
      handle->m[i].pos = 0;
      /* direction pin */
      gpio_config.isInput = false; /* direction pin is output only */
      memcpy(&gpio_config.hw, &config->motor[i].hw_dir, sizeof(gpio_config.hw)); /* copy hardware info */
      gpio_config.isHighOnInit = false;
      handle->m[i].dir = McuGPIO_InitGPIO(&gpio_config); /* create gpio handle */
      McuX12_017_SetForward(handle, i); /* make sure that motor is initialized with direction */
    }
  }
  return handle;
}

void McuX12_017_ResetDriver(McuX12_017_Handle_t device) {
  /* RESET line shall be low during power-on (e.g. with pull-down resistor), then can be released after 1ms after power-on */
  McuX12_Device_t *dev = (McuX12_Device_t*)device;

  if (dev->hasReset) {
    McuGPIO_SetLow(dev->reset);
    McuWait_Waitms(1);
    McuGPIO_SetHigh(dev->reset); /* reset is low active */
    McuWait_Waitus(10);
  }
}

void McuX12_017_SetResetLine(McuX12_017_Handle_t device, bool setHigh) {
  /* RESET is low-active */
  McuX12_Device_t *dev = (McuX12_Device_t*)device;

  if (dev!=NULL && dev->hasReset) {
    McuGPIO_SetValue(dev->reset, setHigh);
  }
}

void McuX12_017_SetForward(McuX12_017_Handle_t device, McuX12_017_Motor_e motor) {
  McuX12_Device_t *dev = (McuX12_Device_t*)device;

  McuGPIO_SetValue(dev->m[motor].dir, !dev->m[motor].isInverted);
  dev->m[motor].isForward = true;
  McuWait_Waitus(10);
}

void McuX12_017_SetBackward(McuX12_017_Handle_t device, McuX12_017_Motor_e motor) {
  McuX12_Device_t *dev = (McuX12_Device_t*)device;

  McuGPIO_SetValue(dev->m[motor].dir, dev->m[motor].isInverted);
  dev->m[motor].isForward = false;
  McuWait_Waitus(10);
}

void McuX12_017_Step(McuX12_017_Handle_t device, McuX12_017_Motor_e motor) {
  McuX12_Device_t *dev = (McuX12_Device_t*)device;

  McuGPIO_SetHigh(dev->m[motor].step);
  McuWait_Waitus(10);
  McuGPIO_SetLow(dev->m[motor].step);
  McuWait_Waitus(100);
  if (dev->m[motor].isForward) {
    dev->m[motor].pos++;
  } else {
    dev->m[motor].pos--;
  }
}

void McuX12_017_DoSteps(McuX12_017_Handle_t device, McuX12_017_Motor_e motor, int32_t steps) {
  McuX12_Device_t *dev = (McuX12_Device_t*)device;

  if (steps>=0 && !dev->m[motor].isForward) {
    McuX12_017_SetForward(device, motor);
  } else if (steps<0 && dev->m[motor].isForward) {
    McuX12_017_SetBackward(device, motor);
  }
  if (steps<0) {
    steps = -steps;
  }
  while(steps>0) {
    McuX12_017_Step(device, motor);
    steps--;
  }
}

void McuX12_017_SingleStep(McuX12_017_Handle_t device, McuX12_017_Motor_e motor, int step) {
  McuX12_Device_t *dev = (McuX12_Device_t*)device;

  if (step<=0 && dev->m[motor].isForward) { /* change direction */
    McuX12_017_SetBackward(dev, motor);
  } else if (step>0 && !dev->m[motor].isForward) { /* change direction */
    McuX12_017_SetForward(dev, motor);
  }
  McuGPIO_SetHigh(dev->m[motor].step); /* do step, next statements will do an implicit delay */
  /* change position information */
  if (dev->m[motor].isForward) {
    dev->m[motor].pos++;
  } else {
    dev->m[motor].pos--;
  }
  McuGPIO_SetLow(dev->m[motor].step);
}

int32_t X12_017_GetPos(McuX12_017_Handle_t device, McuX12_017_Motor_e motor) {
  McuX12_Device_t *dev = (McuX12_Device_t*)device;
  return dev->m[motor].pos;
}

void X12_017_SetPos(McuX12_017_Handle_t device, McuX12_017_Motor_e motor, int32_t pos) {
  McuX12_Device_t *dev = (McuX12_Device_t*)device;
  dev->m[motor].pos = pos;
}

void McuX12_017_GetDeviceStatusString(McuX12_017_Handle_t device, unsigned char *buf, size_t bufSize) {
  McuX12_Device_t *dev = (McuX12_Device_t*)device;

  *buf = '\0';
  McuUtility_strcat(buf, bufSize, (unsigned char*)"reset:");
  if (dev->hasReset) {
    McuUtility_strcat(buf, bufSize, (unsigned char*)"y, ");
  } else {
    McuUtility_strcat(buf, bufSize, (unsigned char*)"n, ");
  }
  for(McuX12_017_Motor_e m=X12_017_M0; m<X12_017_NOF_M; m++) {
    McuUtility_strcat(buf, bufSize, (unsigned char*)"m[");
    McuUtility_strcatNum32u(buf, bufSize, m);
    McuUtility_strcat(buf, bufSize, (unsigned char*)"]: pos:");
    McuUtility_strcatNum32s(buf, bufSize, dev->m[m].pos);
    McuUtility_strcat(buf, bufSize, (unsigned char*)" fw:");
    if (dev->m[m].isForward) {
      McuUtility_strcat(buf, bufSize, (unsigned char*)"y ");
    } else {
      McuUtility_strcat(buf, bufSize, (unsigned char*)"n ");
    }
    McuUtility_strcat(buf, bufSize, (unsigned char*)"inv:");
    if (dev->m[m].isInverted) {
      McuUtility_strcat(buf, bufSize, (unsigned char*)"y ");
    } else {
      McuUtility_strcat(buf, bufSize, (unsigned char*)"n ");
    }
  }
}

void McuX12_017_DisableDevice(McuX12_017_Handle_t device) {
  McuX12_Device_t *x12 = (McuX12_Device_t*)device;

  if (x12->hasReset) {
    McuGPIO_SetAsInput(x12->reset);
  }
  for(int i=0; i<X12_017_NOF_M; i++) {
    McuGPIO_SetAsInput(x12->m[i].dir);
    McuGPIO_SetAsInput(x12->m[i].step);
  }
}

void McuX12_017_EnableDevice(McuX12_017_Handle_t device) {
  McuX12_Device_t *x12 = (McuX12_Device_t*)device;

  if (x12->hasReset) {
    McuGPIO_SetAsOutput(x12->reset, true);
  }
  for(int i=0; i<X12_017_NOF_M; i++) {
    if (x12->m[i].isForward) { /* set pin according to current direction state */
      McuGPIO_SetAsOutput(x12->m[i].dir, !x12->m[i].isInverted);
    } else {
      McuGPIO_SetAsOutput(x12->m[i].dir, x12->m[i].isInverted);
    }
    McuGPIO_SetAsOutput(x12->m[i].step, false);
  }
}

void McuX12_017_Deinit(void) {
  /* nothing needed */
}

void McuX12_017_Init(void) {
  /* nothing needed */
}

