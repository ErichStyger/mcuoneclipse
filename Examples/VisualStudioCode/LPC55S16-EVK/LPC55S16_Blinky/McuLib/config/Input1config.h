/**
 * \file
 * \brief Configuration header file for SDK_BitIO
 * Copyright (c) 2020, Erich Styger
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * This header file is used to configure settings of the SDK Bit I/O module.
 */

#ifndef __Input1_CONFIG_H
#define __Input1_CONFIG_H

#if McuLib_CONFIG_SDK_VERSION_USED == McuLib_CONFIG_SDK_MCUXPRESSO_2_0
  #include "pin_mux.h" /* include pin muxing header file */

  #if defined(BOARD_INITPINS_Input1_PIN)
    #define Input1_CONFIG_PIN_NUMBER    BOARD_INITPINS_Input1_PIN
  #endif
  #if defined(BOARD_INITPINS_Input1_GPIO)
    #define Input1_CONFIG_GPIO_NAME     BOARD_INITPINS_Input1_GPIO
  #endif
  #if defined(BOARD_INITPINS_Input1_PORT)
    #define Input1_CONFIG_PORT_NAME     BOARD_INITPINS_Input1_PORT
  #endif
#endif

#ifndef Input1_CONFIG_PORT_NAME
  #if McuLib_CONFIG_CPU_IS_IMXRT
    #define Input1_CONFIG_PORT_NAME       GPIO1
  #elif McuLib_CONFIG_CPU_IS_LPC
    #define Input1_CONFIG_PORT_NAME       0
  #else /* name from properties */
    #define Input1_CONFIG_PORT_NAME       PORTA
  #endif
    /*!< name of PORT, is pointer to PORT_Type */
#endif

#ifndef Input1_CONFIG_GPIO_NAME
  #if McuLib_CONFIG_CPU_IS_IMXRT
    #define Input1_CONFIG_GPIO_NAME       GPIO1
  #elif McuLib_CONFIG_CPU_IS_LPC
    #define Input1_CONFIG_GPIO_NAME       GPIO
  #elif McuLib_CONFIG_CPU_IS_KINETIS && McuLib_CONFIG_IS_KINETIS_KE
    #define Input1_CONFIG_GPIO_NAME       0
  #else /* name from properties */
    #define Input1_CONFIG_GPIO_NAME       GPIOA
  #endif
    /*!< name of GPIO, is pointer to GPIO_Type, not used for S32K SDK */
#endif

#ifndef Input1_CONFIG_PIN_NUMBER
  #define Input1_CONFIG_PIN_NUMBER      0u
    /*!< number of pin, type unsigned integer */
#endif

#ifndef Input1_CONFIG_PIN_SYMBOL
  #define Input1_CONFIG_PIN_SYMBOL      LED_RED
    /*!< symbolic name for pin, used for NXP SDK V1.3 */
#endif

#ifndef Input1_CONFIG_INIT_PIN_VALUE
  #define Input1_CONFIG_INIT_PIN_VALUE  0
  /*!< 0: Pin data is initialized with 0 (low); 1: pin value is initialized with 1 (high) */
#endif

/* different types of pin direction settings */
#define Input1_CONFIG_INIT_PIN_DIRECTION_NONE    (0)
#define Input1_CONFIG_INIT_PIN_DIRECTION_INPUT   (1)
#define Input1_CONFIG_INIT_PIN_DIRECTION_OUTPUT  (2)

#ifndef Input1_CONFIG_INIT_PIN_DIRECTION
  #define Input1_CONFIG_INIT_PIN_DIRECTION  Input1_CONFIG_INIT_PIN_DIRECTION_INPUT
#endif

#ifndef Input1_CONFIG_DO_PIN_MUXING
  #define Input1_CONFIG_DO_PIN_MUXING  0
  /*!< 1: perform pin muxing in Init(), 0: do not do pin muxing */
#endif

#ifndef Input1_CONFIG_PULL_RESISTOR
  #define Input1_CONFIG_PULL_RESISTOR  0
  /*!< pull resistor setting. 0: no pull resistor, 1: pull-up, 2: pull-down, 3: pull-up or no pull, 4: pull-down or no pull: 4: autoselect-pull */
#endif

#endif /* __Input1_CONFIG_H */
