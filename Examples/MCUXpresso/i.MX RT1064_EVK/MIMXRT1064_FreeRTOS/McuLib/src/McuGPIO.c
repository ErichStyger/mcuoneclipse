/*
 * Copyright (c) 2019-2021, Erich Styger
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
#if McuLib_CONFIG_NXP_SDK_USED
  #include "fsl_gpio.h"
#elif McuLib_CONFIG_CPU_IS_STM32
#endif
#if McuLib_CONFIG_CPU_IS_KINETIS
  #include "fsl_port.h"
#elif McuLib_CONFIG_CPU_IS_LPC
  #include "fsl_iocon.h"
#elif McuLib_CONFIG_CPU_IS_IMXRT
  #include "fsl_iomuxc.h"
#elif McuLib_CONFIG_CPU_IS_STM32
  #include "stm32f3xx_hal.h"
#elif McuLib_CONFIG_CPU_IS_ESP32
  #include "driver/gpio.h"
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
      #if McuLib_CONFIG_NXP_SDK_USED
        .gpio = NULL,
      #elif McuLib_CONFIG_CPU_IS_STM32
        .gpio = NULL,
      #endif
    #if McuLib_CONFIG_CPU_IS_KINETIS
      .port = NULL,
    #elif McuLib_CONFIG_CPU_IS_LPC && McuLib_CONFIG_CORTEX_M==0
      .port = 0,
      .iocon = -1,
    #elif McuLib_CONFIG_CPU_IS_LPC
      .port = 0,
    #endif
    #if McuLib_CONFIG_CPU_IS_ESP32
      .pin = GPIO_NUM_NC,
    #else
      .pin = 0,
    #endif
      .pull = McuGPIO_PULL_DISABLE,
    }
};

typedef struct {
#if McuLib_CONFIG_CPU_IS_ESP32
  bool isHigh; /* status of output pin, because we cannot toggle pin */
#endif
  bool isInput;
  McuGPIO_HwPin_t hw;
} McuGPIO_t;

void McuGPIO_GetDefaultConfig(McuGPIO_Config_t *config) {
  assert(config!=NULL);
  memcpy(config, &defaultConfig, sizeof(*config));
}

static void McuGPIO_ConfigurePin(McuGPIO_t *pin, bool isInput, bool isHighOnInit) {
#if McuLib_CONFIG_NXP_SDK_USED
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
  GPIO_PinInit(pin->hw.gpio, pin->hw.pin, &pin_config);
#elif McuLib_CONFIG_CPU_IS_LPC
  GPIO_PinInit(pin->hw.gpio, pin->hw.port, pin->hw.pin, &pin_config);
#elif McuLib_CONFIG_CPU_IS_IMXRT
  GPIO_PinInit(pin->hw.gpio, pin->hw.pin, &pin_config);
#endif
#elif McuLib_CONFIG_CPU_IS_STM32
  GPIO_InitTypeDef config;

  /* setup initialization structure */
  config.Alternate = 0; /* init */
  if (isInput) {
    config.Mode = GPIO_MODE_INPUT; /* configure as input pin */
  } else {
    config.Mode = GPIO_MODE_OUTPUT_PP; /* configure as push/pull output pin */
  }
  switch(hw->pull) {
    case McuGPIO_PULL_DISABLE: config.Pull = GPIO_NOPULL; break;
    case McuGPIO_PULL_UP: config.Pull = GPIO_PULLUP; break;
    case McuGPIO_PULL_DOWN: config.Pull = GPIO_PULLDOWN; break;
  }
  config.Speed = GPIO_SPEED_FREQ_LOW;
  config.Pin = pin->hw.pin;
  HAL_GPIO_Init(pin->hw.gpio, &config);
  /* write default output level */
  if (!isInput) {
    HAL_GPIO_WritePin(pin->hw.gpio, pin->hw.pin, isHighOnInit?GPIO_PIN_SET:GPIO_PIN_RESET);
  }
#elif McuLib_CONFIG_CPU_IS_ESP32
  gpio_pad_select_gpio(pin->hw.pin);
  if (isInput) {
    gpio_set_direction(pin->hw.pin, GPIO_MODE_INPUT);
  } else {
    gpio_set_direction(pin->hw.pin, GPIO_MODE_OUTPUT);
  }
  switch(pin->hw.pull) {
    case McuGPIO_PULL_DISABLE: gpio_set_pull_mode(pin->hw.pin, GPIO_FLOATING); break;
    case McuGPIO_PULL_UP:      gpio_set_pull_mode(pin->hw.pin, GPIO_PULLUP_ONLY); break;
    case McuGPIO_PULL_DOWN:    gpio_set_pull_mode(pin->hw.pin, GPIO_PULLDOWN_ONLY); break;
  }
  if (!isInput) {
    gpio_set_level(pin->hw.pin, isHighOnInit?1:0);
    pin->isHigh = isHighOnInit;
  }
#endif
}

void McuGPIO_SetAsInput(McuGPIO_Handle_t gpio) {
  McuGPIO_t *pin = (McuGPIO_t*)gpio;

  assert(gpio!=NULL);
  McuGPIO_ConfigurePin(pin, true, false /* don't care */);
  pin->isInput = true;
}

void McuGPIO_SetAsOutput(McuGPIO_Handle_t gpio, bool setHigh) {
  McuGPIO_t *pin = (McuGPIO_t*)gpio;

  assert(gpio!=NULL);
  McuGPIO_ConfigurePin(pin, false, setHigh);
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

#if McuLib_CONFIG_CPU_IS_IMXRT
void McuGPIO_SetMux(McuGPIO_HwPin_t *hw, uint32_t muxRegister, uint32_t muxMode, uint32_t inputRegister, uint32_t inputDaisy, uint32_t configRegister) {
  hw->mux.muxRegister = muxRegister;
  hw->mux.muxMode = muxMode;
  hw->mux.inputRegister = inputRegister;
  hw->mux.inputDaisy = inputDaisy;
  hw->mux.configRegister = configRegister;
}
#endif

McuGPIO_Handle_t McuGPIO_InitGPIO(McuGPIO_Config_t *config) {
  McuGPIO_t *handle;

  assert(config!=NULL);
  /* allocate memory for handle */
#if MCUGPIO_CONFIG_USE_FREERTOS_HEAP
  handle = (McuGPIO_t*)pvPortMalloc(sizeof(McuGPIO_t)); /* get a new device descriptor */
#else
  handle = (McuGPIO_t*)malloc(sizeof(McuGPIO_t)); /* get a new device descriptor */
#endif
  assert(handle!=NULL);
  if (handle!=NULL) { /* if malloc failed, will return NULL pointer */
    memset(handle, 0, sizeof(McuGPIO_t)); /* init all fields */
    handle->isInput = config->isInput;
    memcpy(&handle->hw, &config->hw, sizeof(handle->hw)); /* copy hardware information */
  }
  McuGPIO_ConfigurePin(handle, config->isInput, config->isHighOnInit);
  /* do the pin muxing */
#if McuLib_CONFIG_CPU_IS_KINETIS
  PORT_SetPinMux(config->hw.port, config->hw.pin, kPORT_MuxAsGpio);
#elif McuLib_CONFIG_CPU_IS_LPC && McuLib_CONFIG_CORTEX_M==0 /* e.g. LPC845 */
  const uint32_t IOCON_config = (McuGPIO_IOCON_PIO_MODE_PULL_INACTIVE | McuGPIO_IOCON_PIO_DEFAULTS);
  assert(config->hw.iocon!=-1); /* must be set! */
  IOCON_PinMuxSet(IOCON, config->hw.iocon, IOCON_config);
#elif McuLib_CONFIG_CPU_IS_LPC && McuLib_CONFIG_CORTEX_M==33 /* LPC55S69 for LPC55S16 */
  #define _IOCON_PIO_DIGITAL_EN 0x0100u  /*!<@brief Enables digital function */
  #define _IOCON_PIO_FUNC0 0x00u         /*!<@brief Selects pin function 0 */
  #define _IOCON_PIO_INV_DI 0x00u        /*!<@brief Input function is not inverted */
  #define _IOCON_PIO_MODE_PULLUP 0x20u   /*!<@brief Selects pull-up function */
  #define _IOCON_PIO_OPENDRAIN_DI 0x00u  /*!<@brief Open drain is disabled */
  #define _IOCON_PIO_SLEW_STANDARD 0x00u /*!<@brief Standard mode, output slew rate control is enabled */

  static const uint32_t port_pin_config = (
                                      _IOCON_PIO_FUNC0 |
                                      /* Selects pull-up function */
                                      _IOCON_PIO_MODE_PULLUP |
                                      /* Standard mode, output slew rate control is enabled */
                                      _IOCON_PIO_SLEW_STANDARD |
                                      /* Input function is not inverted */
                                      _IOCON_PIO_INV_DI |
                                      /* Enables digital function */
                                      _IOCON_PIO_DIGITAL_EN |
                                      /* Open drain is disabled */
                                      _IOCON_PIO_OPENDRAIN_DI);
  IOCON_PinMuxSet(IOCON, config->hw.port, config->hw.pin, port_pin_config);
#elif McuLib_CONFIG_CPU_IS_IMXRT
  IOMUXC_SetPinMux( handle->hw.mux.muxRegister,
                    handle->hw.mux.muxMode,
                    handle->hw.mux.inputRegister,
                    handle->hw.mux.inputDaisy,
                    handle->hw.mux.configRegister,
                    0U);
#if McuLib_CONFIG_CPU_VARIANT==McuLib_CONFIG_CPU_VARIANT_NXP_IMXRT1064
  /* GPIO1 and GPIO6 share same IO MUX function, configured in GPR26 */
  if (handle->hw.gpio==GPIO1) {
    IOMUXC_GPR->GPR26 &= ~(1<<handle->hw.pin); /* 0: GPIO1, 1: GPIO6 */
  } else if (handle->hw.gpio==GPIO6) {
    IOMUXC_GPR->GPR26 |= (1<<handle->hw.pin);  /* 0: GPIO1, 1: GPIO6 */

  /* GPIO2 and GPIO7 share same IO MUX function, configured in GPR27 */
  } else if (handle->hw.gpio==GPIO2) {
    IOMUXC_GPR->GPR27 &= (1<<handle->hw.pin);  /* 0: GPIO2, 1: GPIO7 */
  } else if (handle->hw.gpio==GPIO7) {
    IOMUXC_GPR->GPR27 |= (1<<handle->hw.pin);  /* 0: GPIO2, 1: GPIO7 */

  /* GPIO3 and GPIO8 share same IO MUX function, configured in GPR28 */
  } else if (handle->hw.gpio==GPIO3) {
    IOMUXC_GPR->GPR28 &= (1<<handle->hw.pin);  /* 0: GPIO3, 1: GPIO8 */
  } else if (handle->hw.gpio==GPIO8) {
    IOMUXC_GPR->GPR28 |= (1<<handle->hw.pin);  /* 0: GPIO3, 1: GPIO8 */

  /* GPIO4 and GPIO9 share same IO MUX function, configured in GPR29 */
  } else if (handle->hw.gpio==GPIO4) {
    IOMUXC_GPR->GPR29 &= (1<<handle->hw.pin);  /* 0: GPIO4, 1: GPIO9 */
  } else if (handle->hw.gpio==GPIO9) {
    IOMUXC_GPR->GPR29 |= (1<<handle->hw.pin);  /* 0: GPIO4, 1: GPIO9 */
  }
#endif /* McuLib_CONFIG_CPU_VARIANT_NXP_IMXRT1064 */
#elif McuLib_CONFIG_CPU_IS_STM32
  /* no muxing */
#elif McuLib_CONFIG_CPU_IS_ESP32
 /* no muxing needed */
#endif
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
#elif McuLib_CONFIG_CPU_IS_STM32
  HAL_GPIO_WritePin(pin->hw.gpio, pin->hw.pin, GPIO_PIN_RESET);
#elif McuLib_CONFIG_CPU_IS_ESP32
  gpio_set_level(pin->hw.pin, 0); /* low */
  pin->isHigh = false;
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
#elif McuLib_CONFIG_CPU_IS_STM32
  HAL_GPIO_WritePin(pin->hw.gpio, pin->hw.pin, GPIO_PIN_SET);
#elif McuLib_CONFIG_CPU_IS_ESP32
  gpio_set_level(pin->hw.pin, 1); /* high */
  pin->isHigh = true;
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
#elif McuLib_CONFIG_CPU_IS_STM32
  HAL_GPIO_TogglePin(pin->hw.gpio, pin->hw.pin);
#elif McuLib_CONFIG_CPU_IS_ESP32
  if (pin->isHigh) {
    gpio_set_level(pin->hw.pin, 0);
    pin->isHigh = false;
  } else {
    gpio_set_level(pin->hw.pin, 1);
    pin->isHigh = true;
  }
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
#elif McuLib_CONFIG_CPU_IS_STM32
  HAL_GPIO_WritePin(pin->hw.gpio, pin->hw.pin, GPIO_PIN_RESET);
#elif McuLib_CONFIG_CPU_IS_ESP32
  gpio_set_level(pin->hw.pin, 1); /* high */
  pin->isHigh = true;
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
#elif McuLib_CONFIG_CPU_IS_STM32
  HAL_GPIO_WritePin(pin->hw.gpio, pin->hw.pin, GPIO_PIN_SET);
#elif McuLib_CONFIG_CPU_IS_ESP32
  gpio_set_level(pin->hw.pin, 0); /* low */
  pin->isHigh = false;
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
#elif McuLib_CONFIG_CPU_IS_STM32
  return HAL_GPIO_ReadPin(pin->hw.gpio, pin->hw.pin);
#elif McuLib_CONFIG_CPU_IS_ESP32
  return gpio_get_level(pin->hw.pin);
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
#if McuLib_CONFIG_NXP_SDK_USED || McuLib_CONFIG_CPU_IS_STM32
  McuUtility_strcat(buf, bufSize, (unsigned char*)", gpio:0x");
  McuUtility_strcatNum32Hex(buf, bufSize, (uint32_t)pin->hw.gpio); /* write address */
#endif
#if McuLib_CONFIG_CPU_IS_KINETIS
  McuUtility_strcat(buf, bufSize, (unsigned char*)", port:0x");
  McuUtility_strcatNum32Hex(buf, bufSize, (uint32_t)pin->hw.port); /* write address */
#elif McuLib_CONFIG_CPU_IS_LPC /* all LPC, including M33 and M0+ */
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

  pin->hw.pull = pull;
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
#elif McuLib_CONFIG_CPU_IS_LPC && McuLib_CONFIG_CORTEX_M==0 /* e.g. LPC845 */
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
  uint32_t config;

  /*! IOCON_PIO_MODE:
   *  MODE - Selects function mode (on-chip pull-up/pull-down resistor control).
   *  0b00..Inactive. Inactive (no pull-down/pull-up resistor enabled).
   *  0b01..Pull-down. Pull-down resistor enabled.
   *  0b10..Pull-up. Pull-up resistor enabled.
   *  0b11..Repeater. Repeater mode.
   */
  if (pull == McuGPIO_PULL_DISABLE) {
    config = IOCON_PIO_MODE(0b00); /* inactive */
  } else if (pull == McuGPIO_PULL_UP) {
    config = IOCON_PIO_MODE(0b10); /* pull-up */
  } else if (pull == McuGPIO_PULL_DOWN) {
    config = IOCON_PIO_MODE(0b01); /* pull-down */
  } else { /* default */
    config = IOCON_PIO_MODE(0b00); /* inactive */
  }
  IOCON->PIO[pin->hw.port][pin->hw.pin] = ((IOCON->PIO[pin->hw.port][pin->hw.pin] &
                       (~(IOCON_PIO_MODE_MASK))) /* Mask bits to zero which are setting */
                      | config); /* Select function mode (on-chip pull-up/pull-down resistor control) */
#elif McuLib_CONFIG_CPU_IS_IMXRT
  if (pin->hw.mux.configRegister!=0) {
    uint32_t configValue; /* configuration of IOMUXC SW_PAD_CTL (hw.mux.configRegister) */

    configValue = *((volatile uint32_t *)pin->hw.mux.configRegister); /* read current config */
    #if 0
    configValue = (0<<16) /* Hysteresis enable field: 0: hysteresis disabled */
        | (0b00<<14) /* pull-up/down: 00: 100k Ohm pull-down, 01: 47k pull-up, 10: 100k pull-up, 11: 22k pull-up */
        | (0<<13) /* pull/keep select: 0: keeper, 1: pull */
        | (0<<12) /* pull/keep enable: 0: disabled, 1: enabled */
        | (0<<11) /* open drain: 0: disabled, 1: enabled */
        | (0b00<<6) /* speed: 00: 50 MHz, 01: 100 MHz, 10: 100 MHz, 11: 200 MHz */
        | (0b000<<3) /* drive strength: 000: disabled */
        | (0<<0) /* slew rage: 0: slow slew rate, 1: fast slew rate */
         ;
    #endif
    /* masking out the bits we are going to set: */
    configValue &= ~((0b11<<14) /* pull-up/down */
                  | (1<<13)     /* pull/keep select: */
                  | (1<<12));   /* pull/keep enable */
    if (pull == McuGPIO_PULL_DISABLE) {
      configValue |= (0b00<<14) /* pull-up/down: 00: 100k Ohm pull-down, 01: 47k pull-up, 10: 100k pull-up, 11: 22k pull-up */
                   | (0<<13) /* pull/keep select: 0: keeper, 1: pull */
                   | (0<<12); /* pull/keep enable: 0: disabled, 1: enabled */
    } else if (pull == McuGPIO_PULL_UP) { /* 100k pull-up */
      configValue |= (0b10<<14) /* pull-up/down: 00: 100k Ohm pull-down, 01: 47k pull-up, 10: 100k pull-up, 11: 22k pull-up */
                   | (1<<13) /* pull/keep select: 0: keeper, 1: pull */
                   | (1<<12); /* pull/keep enable: 0: disabled, 1: enabled */
    } else if (pull == McuGPIO_PULL_DOWN) { /* 100k pull-down */
      configValue |= (0b00<<14) /* pull-up/down: 00: 100k Ohm pull-down, 01: 47k pull-up, 10: 100k pull-up, 11: 22k pull-up */
                   | (1<<13) /* pull/keep select: 0: keeper, 1: pull */
                   | (1<<12); /* pull/keep enable: 0: disabled, 1: enabled */
    }
    IOMUXC_SetPinConfig(pin->hw.mux.muxRegister,
                        pin->hw.mux.muxMode,
                        pin->hw.mux.inputRegister,
                        pin->hw.mux.inputDaisy,
                        pin->hw.mux.configRegister,
                        configValue);
  }
#elif McuLib_CONFIG_CPU_IS_STM32 
  McuGPIO_ConfigurePin(pin->isInput, false /* don't care as only for output */, &pin->hw);
#elif McuLib_CONFIG_CPU_IS_ESP32
  /* NYI */
#endif
}

void McuGPIO_Init(void) {
  /* nothing to do */
}

void McuGPIO_Deinit(void) {
  /* nothing to do */
}
