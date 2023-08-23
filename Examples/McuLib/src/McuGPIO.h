/*
 * Copyright (c) 2019-2021, Erich Styger
 * All rights reserved.
 *
 * Driver for GPIO pins
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef McuGPIO_H_
#define McuGPIO_H_

#include <stdint.h>
#include <stddef.h>
#include "McuLib.h"
#if McuLib_CONFIG_NXP_SDK_USED
  #include "fsl_gpio.h"
  #if McuLib_CONFIG_IS_KINETIS_KE
    #include "fsl_port.h"
  #endif
#elif McuLib_CONFIG_SDK_VERSION_USED==McuLib_CONFIG_SDK_LINUX
  #include <gpiod.h>
#elif McuLib_CONFIG_CPU_IS_STM32
  #include "stm32f3xx_hal.h"
#elif McuLib_CONFIG_CPU_IS_ESP32
  #include "driver/gpio.h"
#elif McuLib_CONFIG_CPU_IS_RPxxxx
  #include "hardware/gpio.h"
#elif McuLib_CONFIG_CPU_IS_IMXRT
  #include "fsl_iomuxc.h"
#endif
#include "McuLibconfig.h"
#include "McuGPIOconfig.h"
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum McuGPIO_PullType {
  McuGPIO_PULL_DISABLE,
  McuGPIO_PULL_UP,
  McuGPIO_PULL_DOWN,
} McuGPIO_PullType;

typedef struct McuGPIO_Dummy_s { int dummy; } McuGPIO_Dummy_s; /*!< using a pointer to a struct instead a pointer to void for handle, used for handle type 'safety' only */

typedef McuGPIO_Dummy_s *McuGPIO_Handle_t; /*!< GPIO handle type */

typedef struct McuGPIO_HwPin_t {
#if McuLib_CONFIG_NXP_SDK_USED && !McuLib_CONFIG_IS_KINETIS_KE
  GPIO_Type *gpio; /* pointer to GPIO */
#elif McuLib_CONFIG_CPU_IS_STM32
  GPIO_TypeDef *gpio;
#elif McuLib_CONFIG_SDK_VERSION_USED==McuLib_CONFIG_SDK_LINUX
  struct gpiod_chip *chip; /* must be retrieved once, e.g.e with gpiod_chip_open_by_name("gpiochip0") */
  const char *name; /* assigned name for the pin */
#endif
#if McuLib_CONFIG_CPU_IS_KINETIS
  PORT_Type *port; /* pointer to port, e.g. PORTA, for KE this is PORT */
  #if McuLib_CONFIG_IS_KINETIS_KE
  port_type_t portType; /* e.g. kPORT_PTH */
  gpio_port_num_t portNum; /* e.g. kGPIO_PORTH */
  #endif
#elif McuLib_CONFIG_CPU_IS_LPC && McuLib_CONFIG_CORTEX_M==0
  uint32_t port; /* port number */
  uint8_t iocon; /* I/O Connection index used for muxing, e.g. IOCON_INDEX_PIO0_0 */
#elif McuLib_CONFIG_CPU_IS_LPC
  uint32_t port; /* port number */
#elif McuLib_CONFIG_CPU_IS_IMXRT
  /* information needed for IOMUXC_SetPinMux(), provided e.g. with IOMUXC_GPIO_AD_B0_09_GPIO1_IO09 */
  struct {
    uint32_t muxRegister;     /* pin mux register */
    uint32_t muxMode;         /* pin mux mode */
    uint32_t inputRegister;   /* select input register */
    uint32_t inputDaisy;      /* the input daisy */
    uint32_t configRegister;  /* the configuration register */
  } mux;
#endif
#if McuLib_CONFIG_CPU_IS_ESP32
  gpio_num_t pin; /* pin number, e.g. GPIO_NUM_10 */
#else
  uint32_t pin; /* pin number */
#endif
  McuGPIO_PullType pull; /* pull resistor configuration */
} McuGPIO_HwPin_t;

typedef struct McuGPIO_Config_t {
  bool isInput;
  bool isHighOnInit;
  McuGPIO_HwPin_t hw;
} McuGPIO_Config_t;

#if McuLib_CONFIG_CPU_IS_IMXRT
  /*!
   * \brief Used to set the Muxing configuration.
   * Usage: McuGPIO_SetMux(&config.hw, IOMUXC_GPIO_AD_B0_09_GPIO1_IO09);
   * @param hw Pointer to hardware struct
   * @param muxRegister The muxing register
   * @param muxMode The muxing mode
   * @param inputRegister The input register, 0 for not used
   * @param inputDaisy The input daisy value
   * @param configRegister The configuration register
   */
  void McuGPIO_SetMux(McuGPIO_HwPin_t *hw, uint32_t muxRegister, uint32_t muxMode, uint32_t inputRegister, uint32_t inputDaisy, uint32_t configRegister);
#endif

void McuGPIO_GetDefaultConfig(McuGPIO_Config_t *config);

McuGPIO_Handle_t McuGPIO_InitGPIO(McuGPIO_Config_t *config);

McuGPIO_Handle_t McuGPIO_DeinitGPIO(McuGPIO_Handle_t gpio);

void McuGPIO_SetAsInput(McuGPIO_Handle_t gpio);
void McuGPIO_SetAsOutput(McuGPIO_Handle_t gpio, bool setHigh);
bool McuGPIO_IsInput(McuGPIO_Handle_t gpio);
bool McuGPIO_IsOutput(McuGPIO_Handle_t gpio);
void McuGPIO_SetLow(McuGPIO_Handle_t gpio);
void McuGPIO_SetHigh(McuGPIO_Handle_t gpio);
void McuGPIO_Toggle(McuGPIO_Handle_t gpio);
bool McuGPIO_IsLow(McuGPIO_Handle_t gpio);
bool McuGPIO_IsHigh(McuGPIO_Handle_t gpio);
void McuGPIO_SetValue(McuGPIO_Handle_t gpio, bool val);
bool McuGPIO_GetValue(McuGPIO_Handle_t gpio);

void McuGPIO_GetPinStatusString(McuGPIO_Handle_t gpio, unsigned char *buf, size_t bufSize);

void McuGPIO_SetPullResistor(McuGPIO_Handle_t gpio, McuGPIO_PullType pull);

/* driver initialization */
void McuGPIO_Init(void);

/* driver de-initialization */
void McuGPIO_Deinit(void);

#ifdef __cplusplus
}  /* extern "C" */
#endif

#endif /* McuGPIO_H_ */
