/*
 * Copyright (c) 2019, Erich Styger
 *
 * Driver for GPIO pins
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "McuLibconfig.h"
#include "McuGPIO.h"
#include "McuUtility.h"
#include <stddef.h>
#include <string.h> /* for memset */
#include <assert.h>
#if MCUGPIO_CONFIG_USE_FREERTOS_HEAP
  #include "McuRTOS.h"
#endif
#include "fsl_gpio.h"
#if McuLib_CONFIG_CPU_IS_KINETIS
  #include "fsl_port.h"
#elif McuLib_CONFIG_CPU_IS_LPC && McuLib_CONFIG_CORTEX_M==0 /* LPC845 */
  #include "fsl_iocon.h"
#endif

#if McuLib_CONFIG_CPU_IS_LPC && McuLib_CONFIG_CORTEX_M==0 /* LPC845 specific defines, not available in SDK */
  #define McuGPIO_IOCON_PIO_CLKDIV0 0x00u      /*!<@brief IOCONCLKDIV0 */
  #define McuGPIO_IOCON_PIO_HYS_EN 0x20u       /*!<@brief Enable hysteresis */
  #define McuGPIO_IOCON_PIO_INV_DI 0x00u       /*!<@brief Input not invert */

  #define McuGPIO_IOCON_PIO_MODE_PULL_INACTIVE  (0x0u<<3) /* Inactive (no pull-down/pull-up resistor enabled) */
  #define McuGPIO_IOCON_PIO_MODE_PULL_DOWN      (0x1u<<3) /* Pull-down enabled */
  #define McuGPIO_IOCON_PIO_MODE_PULL_UP        (0x2u<<3) /* Pull-up enabled */
  #define McuGPIO_IOCON_PIO_MODE_PULL_REPEATER  (0x3u<<3) /* Repeater mode */

  #define McuGPIO_IOCON_PIO_OD_DI 0x00u        /*!<@brief Disables Open-drain function */
  #define McuGPIO_IOCON_PIO_SMODE_BYPASS 0x00u /*!<@brief Bypass input filter */

  #define McuGPIO_IOCON_PIO_DEFAULTS  \
                /* Enable hysteresis */ \
                McuGPIO_IOCON_PIO_HYS_EN | \
                /* Input not invert */ \
                McuGPIO_IOCON_PIO_INV_DI | \
                /* Disables Open-drain function */ \
                McuGPIO_IOCON_PIO_OD_DI | \
                /* Bypass input filter */ \
                McuGPIO_IOCON_PIO_SMODE_BYPASS | \
                /* IOCONCLKDIV0 */ \
                McuGPIO_IOCON_PIO_CLKDIV0
#endif

/* default configuration, used for initializing the config */
static const McuGPIO_Config_t defaultConfig =
{
    .isInput = true,
    .isHighOnInit = false,
    .hw = {
      .gpio = NULL,
    #if McuLib_CONFIG_CPU_IS_KINETIS
      .port = NULL,
    #elif McuLib_CONFIG_CPU_IS_LPC && McuLib_CONFIG_CORTEX_M==0
      .port = 0,
      .iocon = -1,
    #elif McuLib_CONFIG_CPU_IS_LPC
      .port = 0,
    #endif
      .pin = 0,
    }
};

typedef struct {
  bool isInput;
  McuGPIO_HwPin_t hw;
} McuGPIO_t;

void McuGPIO_GetDefaultConfig(McuGPIO_Config_t *config) {
  assert(config!=NULL);
  memcpy(config, &defaultConfig, sizeof(*config));
}

static void McuGPIO_ConfigureDirection(bool isInput, bool isHighOnInit, McuGPIO_HwPin_t *hw) {
  gpio_pin_config_t pin_config; /* config for the SDK */

  memset(&pin_config, 0, sizeof(pin_config)); /* init all fields */
  if (isInput) {
#if McuLib_CONFIG_CPU_IS_IMXRT
    pin_config.direction = kGPIO_DigitalInput;
#else
    pin_config.pinDirection = kGPIO_DigitalInput;
#endif
  } else {
#if McuLib_CONFIG_CPU_IS_IMXRT
    pin_config.direction = kGPIO_DigitalOutput;
#else
    pin_config.pinDirection = kGPIO_DigitalOutput;
#endif
  }
#if McuLib_CONFIG_CPU_IS_IMXRT
  pin_config.interruptMode = kGPIO_NoIntmode; /* no interrupts */
#endif
  pin_config.outputLogic = isHighOnInit;
#if McuLib_CONFIG_CPU_IS_KINETIS
  GPIO_PinInit(hw->gpio, hw->pin, &pin_config);
#elif McuLib_CONFIG_CPU_IS_LPC
  GPIO_PinInit(hw->gpio, hw->port, hw->pin, &pin_config);
#elif McuLib_CONFIG_CPU_IS_IMXRT
  GPIO_PinInit(hw->gpio, hw->pin, &pin_config);
#endif
}

void McuGPIO_SetAsInput(McuGPIO_Handle_t gpio) {
  McuGPIO_t *pin = (McuGPIO_t*)gpio;

  assert(gpio!=NULL);
  McuGPIO_ConfigureDirection(true, false /* don't care */, &pin->hw);
  pin->isInput = true;
}

void McuGPIO_SetAsOutput(McuGPIO_Handle_t gpio, bool setHigh) {
  McuGPIO_t *pin = (McuGPIO_t*)gpio;

  assert(gpio!=NULL);
  McuGPIO_ConfigureDirection(false, setHigh, &pin->hw);
  pin->isInput = false;
}

bool McuGPIO_IsInput(McuGPIO_Handle_t gpio) {
  McuGPIO_t *pin = (McuGPIO_t*)gpio;
  return pin->isInput;
}

bool McuGPIO_IsOutput(McuGPIO_Handle_t gpio) {
  McuGPIO_t *pin = (McuGPIO_t*)gpio;
  return !pin->isInput;
}

McuGPIO_Handle_t McuGPIO_InitGPIO(McuGPIO_Config_t *config) {
  McuGPIO_t *handle;

  assert(config!=NULL);
  McuGPIO_ConfigureDirection(config->isInput, config->isHighOnInit, &config->hw);
#if McuLib_CONFIG_CPU_IS_KINETIS
  PORT_SetPinMux(config->hw.port, config->hw.pin, kPORT_MuxAsGpio);
#elif McuLib_CONFIG_CPU_IS_LPC && McuLib_CONFIG_CORTEX_M==0 /* e.g. LPC845 */
  const uint32_t IOCON_config = (McuGPIO_IOCON_PIO_MODE_PULL_INACTIVE | McuGPIO_IOCON_PIO_DEFAULTS);

  assert(config->hw.iocon!=-1); /* must be set! */
  IOCON_PinMuxSet(IOCON, config->hw.iocon, IOCON_config);
#elif McuLib_CONFIG_CPU_IS_LPC && McuLib_CONFIG_CORTEX_M==33 /* LPC55S69 */
  /* \todo */
#elif McuLib_CONFIG_CPU_IS_IMXRT
  /* \todo */
#endif
#if MCUGPIO_CONFIG_USE_FREERTOS_HEAP
  handle = (McuGPIO_t*)pvPortMalloc(sizeof(McuGPIO_t)); /* get a new device descriptor */
#else
  handle = (McuGPIO_t*)malloc(sizeof(McuGPIO_t)); /* get a new device descriptor */
#endif
  assert(handle!=NULL);
  if (handle!=NULL) { /* if malloc failed, will return NULL pointer */
    memset(handle, 0, sizeof(McuGPIO_t)); /* init all fields */
    handle->isInput = config->isInput;
    handle->hw.gpio = config->hw.gpio;
    handle->hw.pin = config->hw.pin;
  #if McuLib_CONFIG_CPU_IS_KINETIS || McuLib_CONFIG_CPU_IS_LPC
    handle->hw.port = config->hw.port;
  #endif
  #if McuLib_CONFIG_CPU_IS_LPC && McuLib_CONFIG_CORTEX_M==0
    handle->hw.iocon = config->hw.iocon;
  #endif
  }
  return handle;
}

McuGPIO_Handle_t McuGPIO_DeinitGPIO(McuGPIO_Handle_t gpio) {
  assert(gpio!=NULL);
#if MCUGPIO_CONFIG_USE_FREERTOS_HEAP
  vPortFree(gpio);
#else
  free(gpio);
#endif
  return NULL;
}

void McuGPIO_SetLow(McuGPIO_Handle_t gpio) {
  assert(gpio!=NULL);
  McuGPIO_t *pin = (McuGPIO_t*)gpio;

#if McuLib_CONFIG_CPU_IS_KINETIS
  #if McuLib_CONFIG_SDK_VERSION < 250
  GPIO_ClearPinsOutput(pin->hw.gpio, (1<<pin->hw.pin));
  #else
  GPIO_PortClear(pin->hw.gpio, (1<<pin->hw.pin));
  #endif
#elif McuLib_CONFIG_CPU_IS_LPC
  GPIO_PortClear(pin->hw.gpio, pin->hw.port, (1<<pin->hw.pin));
#elif McuLib_CONFIG_CPU_IS_IMXRT
  GPIO_PinWrite(pin->hw.gpio, pin->hw.pin, 0U);
#endif
}

void McuGPIO_SetHigh(McuGPIO_Handle_t gpio) {
  assert(gpio!=NULL);
  McuGPIO_t *pin = (McuGPIO_t*)gpio;

#if McuLib_CONFIG_CPU_IS_KINETIS
  #if McuLib_CONFIG_SDK_VERSION < 250
  GPIO_SetPinsOutput(pin->hw.gpio, (1<<pin->hw.pin));
  #else
  GPIO_PortSet(pin->hw.gpio, (1<<pin->hw.pin));
  #endif
#elif McuLib_CONFIG_CPU_IS_LPC
  GPIO_PortSet(pin->hw.gpio, pin->hw.port, (1<<pin->hw.pin));
#elif McuLib_CONFIG_CPU_IS_IMXRT
  GPIO_PinWrite(pin->hw.gpio, pin->hw.pin, 1U);
#endif
}

void McuGPIO_Toggle(McuGPIO_Handle_t gpio) {
  assert(gpio!=NULL);
  McuGPIO_t *pin = (McuGPIO_t*)gpio;

#if McuLib_CONFIG_CPU_IS_KINETIS
  #if McuLib_CONFIG_SDK_VERSION < 250
  GPIO_TogglePinsOutput(pin->hw.gpio, (1<<pin->hw.pin));
  #else
  GPIO_PortToggle(pin->hw.gpio, (1<<pin->hw.pin));
  #endif
#elif McuLib_CONFIG_CPU_IS_LPC
  GPIO_PortToggle(pin->hw.gpio, pin->hw.port, (1<<pin->hw.pin));
#elif McuLib_CONFIG_CPU_IS_IMXRT
  GPIO_PortToggle(pin->hw.gpio, (1<<pin->hw.pin));
#endif
}

void McuGPIO_SetValue(McuGPIO_Handle_t gpio, bool val) {
  assert(gpio!=NULL);
  McuGPIO_t *pin = (McuGPIO_t*)gpio;

  if (val) { /* set to HIGH */
#if McuLib_CONFIG_CPU_IS_KINETIS
  #if McuLib_CONFIG_SDK_VERSION < 250
    GPIO_SetPinsOutput(pin->hw.gpio, (1<<pin->hw.pin));
  #else
    GPIO_PortSet(pin->hw.gpio, (1<<pin->hw.pin));
  #endif
#elif McuLib_CONFIG_CPU_IS_LPC
    GPIO_PortSet(pin->hw.gpio, pin->hw.port, (1<<pin->hw.pin));
#elif McuLib_CONFIG_CPU_IS_IMXRT
    GPIO_PinWrite(pin->hw.gpio, pin->hw.pin, 1U);
#endif
  } else { /* set to LOW */
#if McuLib_CONFIG_CPU_IS_KINETIS
  #if McuLib_CONFIG_SDK_VERSION < 250
    GPIO_ClearPinsOutput(pin->hw.gpio, (1<<pin->hw.pin));
  #else
    GPIO_PortClear(pin->hw.gpio, (1<<pin->hw.pin));
  #endif
#elif McuLib_CONFIG_CPU_IS_LPC
    GPIO_PortClear(pin->hw.gpio, pin->hw.port, (1<<pin->hw.pin));
#elif McuLib_CONFIG_CPU_IS_IMXRT
    GPIO_PinWrite(pin->hw.gpio, pin->hw.pin, 1U);
#endif
  }
}

bool McuGPIO_GetValue(McuGPIO_Handle_t gpio) {
  return McuGPIO_IsHigh(gpio);
}

bool McuGPIO_IsHigh(McuGPIO_Handle_t gpio) {
  assert(gpio!=NULL);
  McuGPIO_t *pin = (McuGPIO_t*)gpio;

#if McuLib_CONFIG_CPU_IS_KINETIS
  #if McuLib_CONFIG_SDK_VERSION < 250
  return GPIO_ReadPinInput(pin->hw.gpio, pin->hw.pin)!=0;
  #else
  return GPIO_PinRead(pin->hw.gpio, pin->hw.pin)!=0;
  #endif
#elif McuLib_CONFIG_CPU_IS_LPC
  return GPIO_PinRead(pin->hw.gpio, pin->hw.port, pin->hw.pin)!=0;
#elif McuLib_CONFIG_CPU_IS_IMXRT
  return GPIO_PinRead(pin->hw.gpio, pin->hw.pin)!=0;
#endif
  return false;
}

bool McuGPIO_IsLow(McuGPIO_Handle_t gpio) {
  return !McuGPIO_IsHigh(gpio);
}

void McuGPIO_GetPinStatusString(McuGPIO_Handle_t gpio, unsigned char *buf, size_t bufSize) {
  McuGPIO_t *pin = (McuGPIO_t*)gpio;

  *buf = '\0';
  if (McuGPIO_IsOutput(gpio)) {
    McuUtility_strcat(buf, bufSize, (unsigned char*)"Output");
  } else {
    McuUtility_strcat(buf, bufSize, (unsigned char*)"Input");
  }
  if (McuGPIO_IsHigh(gpio)) {
    McuUtility_strcat(buf, bufSize, (unsigned char*)", HIGH");
  } else {
    McuUtility_strcat(buf, bufSize, (unsigned char*)", LOW");
  }
  McuUtility_strcat(buf, bufSize, (unsigned char*)", gpio:0x");
  McuUtility_strcatNum32Hex(buf, bufSize, (uint32_t)pin->hw.gpio); /* write address */
#if McuLib_CONFIG_CPU_IS_KINETIS
  McuUtility_strcat(buf, bufSize, (unsigned char*)", port:0x");
  McuUtility_strcatNum32Hex(buf, bufSize, (uint32_t)pin->hw.port); /* write address */
#elif McuLib_CONFIG_CPU_IS_LPC
  McuUtility_strcat(buf, bufSize, (unsigned char*)", port:");
  McuUtility_strcatNum32u(buf, bufSize, (uint32_t)pin->hw.port); /* write port number */
#endif
  McuUtility_strcat(buf, bufSize, (unsigned char*)", pin:");
  McuUtility_strcatNum32u(buf, bufSize, (uint32_t)pin->hw.pin); /* write pin number */
#if McuLib_CONFIG_CPU_IS_LPC && McuLib_CONFIG_CORTEX_M==0
  McuUtility_strcat(buf, bufSize, (unsigned char*)", iocon:");
  McuUtility_strcatNum32u(buf, bufSize, (uint32_t)pin->hw.iocon); /* write IOCON number */
#endif
}

void McuGPIO_SetPullResistor(McuGPIO_Handle_t gpio, McuGPIO_PullType pull) {
  McuGPIO_t *pin = (McuGPIO_t*)gpio;

#if McuLib_CONFIG_CPU_IS_KINETIS
  if (pull == McuGPIO_PULL_DISABLE) {
    pin->hw.port->PCR[pin->hw.pin] = ((pin->hw.port->PCR[pin->hw.pin] &
                      /* Mask bits to zero which are setting */
                      (~(PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_ISF_MASK)))
                     /* Pull Select: Internal pullup resistor is enabled on the corresponding pin, if the
                      * corresponding Port Pull Enable field is set. */
                     | (uint32_t)(kPORT_PullUp)
                     | PORT_PCR_PE(kPORT_PullDisable));
  } else if (pull == McuGPIO_PULL_UP) {
    pin->hw.port->PCR[pin->hw.pin] = ((pin->hw.port->PCR[pin->hw.pin] &
                      /* Mask bits to zero which are setting */
                      (~(PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_ISF_MASK)))

                     /* Pull Select: Internal pullup resistor is enabled on the corresponding pin, if the
                      * corresponding Port Pull Enable field is set. */
                     | (uint32_t)(kPORT_PullUp));
  } else if (pull == McuGPIO_PULL_DOWN) {
    pin->hw.port->PCR[pin->hw.pin] = ((pin->hw.port->PCR[pin->hw.pin] &
                      /* Mask bits to zero which are setting */
                      (~(PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_ISF_MASK)))

                     /* Pull Select: Internal pullup resistor is enabled on the corresponding pin, if the
                      * corresponding Port Pull Enable field is set. */
                     | (uint32_t)(kPORT_PullDown));
  }
#elif McuLib_CONFIG_CPU_IS_LPC && McuLib_CONFIG_CORTEX_M==0
  uint32_t IOCON_config;

  if (pull == McuGPIO_PULL_DISABLE) {
    IOCON_config = ( McuGPIO_IOCON_PIO_MODE_PULL_INACTIVE |  McuGPIO_IOCON_PIO_DEFAULTS);
  } else if (pull == McuGPIO_PULL_UP) {
    IOCON_config = ( McuGPIO_IOCON_PIO_MODE_PULL_UP |  McuGPIO_IOCON_PIO_DEFAULTS);
  } else if (pull == McuGPIO_PULL_DOWN) {
    IOCON_config = ( McuGPIO_IOCON_PIO_MODE_PULL_DOWN |  McuGPIO_IOCON_PIO_DEFAULTS);
  } else {
    IOCON_config = ( McuGPIO_IOCON_PIO_MODE_PULL_INACTIVE |  McuGPIO_IOCON_PIO_DEFAULTS);
  }
  IOCON_PinMuxSet(IOCON, pin->hw.iocon, IOCON_config);
#elif McuLib_CONFIG_CPU_IS_LPC
  if (pull == McuGPIO_PULL_DISABLE) {
  } else if (pull == McuGPIO_PULL_UP) {
  } else if (pull == McuGPIO_PULL_DOWN) {
  }
  /* \todo */
#elif McuLib_CONFIG_CPU_IS_IMXRT
  /* \todo, NYI */
  if (pull == McuGPIO_PULL_DISABLE) {
  } else if (pull == McuGPIO_PULL_UP) {
  } else if (pull == McuGPIO_PULL_DOWN) {
  }
#endif
}

void McuGPIO_Init(void) {
  /* nothing to do */
}

void McuGPIO_Deinit(void) {
  /* nothing to do */
}
