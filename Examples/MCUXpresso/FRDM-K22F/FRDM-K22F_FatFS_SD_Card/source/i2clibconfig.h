/*
 * Copyright (c) 2020, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef I2CLIBCONFIG_H_
#define I2CLIBCONFIG_H_

#include "platform.h"
#include "McuLib.h"

/* I2C GPIO pins, needed to reset the bus */
#if McuLib_CONFIG_CPU_IS_LPC  /* LPC845-BRK */
  #define I2CLIB_SCL_GPIO         GPIO
  #define I2CLIB_SCL_GPIO_PORT    0
  #define I2CLIB_SCL_GPIO_PIN     10
  #define I2CLIB_SDA_GPIO         GPIO
  #define I2CLIB_SDA_GPIO_PORT    0
  #define I2CLIB_SDA_GPIO_PIN     11

  #define I2CLIB_CONFIG_SCL_GPIO_MUXING    kPORT_MuxAlt2
  #define I2CLIB_CONFIG_SDA_GPIO_MUXING    kPORT_MuxAlt2

  #define I2C_MASTER_BASEADDR     I2C0
  #define I2C_MASTER_CLK_FREQ     12000000
#elif McuLib_CONFIG_CPU_IS_KINETIS /* K22FN512 */
  #define CONFIG_I2C_USE_PORT_B     (1) /* SCL PTB0, SDA PTB1 */
  #define CONFIG_I2C_USE_PORT_E     (0) /* SDA PTE0, SCL PTE1 */

  #if CONFIG_I2C_USE_PORT_E
    #define I2CLIB_SCL_GPIO         GPIOE
    #define I2CLIB_SCL_GPIO_PORT    PORTE
    #define I2CLIB_SCL_GPIO_PIN     1u
    #define I2CLIB_SDA_GPIO         GPIOE
    #define I2CLIB_SDA_GPIO_PORT    PORTE
    #define I2CLIB_SDA_GPIO_PIN     0u

    #define I2C_MASTER_BASEADDR     I2C1
    #define I2C_MASTER_CLK_SRC      I2C1_CLK_SRC

    #define I2CLIB_CONFIG_SCL_GPIO_MUXING    kPORT_MuxAlt6
    #define I2CLIB_CONFIG_SDA_GPIO_MUXING    kPORT_MuxAlt6
  #elif CONFIG_I2C_USE_PORT_B
    #define I2CLIB_SCL_GPIO         GPIOB
    #define I2CLIB_SCL_GPIO_PORT    PORTB
    #define I2CLIB_SCL_GPIO_PIN     0u
    #define I2CLIB_SDA_GPIO         GPIOB
    #define I2CLIB_SDA_GPIO_PORT    PORTB
    #define I2CLIB_SDA_GPIO_PIN     1u

    #define I2C_MASTER_BASEADDR     I2C0
    #define I2C_MASTER_CLK_SRC      I2C0_CLK_SRC

    #define I2CLIB_CONFIG_SCL_GPIO_MUXING    kPORT_MuxAlt2
    #define I2CLIB_CONFIG_SDA_GPIO_MUXING    kPORT_MuxAlt2
  #endif

  #define I2C_MASTER_CLK_FREQ     CLOCK_GetFreq(I2C_MASTER_CLK_SRC)
#endif

#define I2C_BAUDRATE            400000U

#define I2C_ADD_DELAY     (1)  /* needed for FXOS sensor? As well for RTC: otherwise the address is not on the bus? */
#define I2C_ADD_DELAY_US  (10)


#endif /* I2CLIBCONFIG_H_ */
