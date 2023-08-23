/*
 * Copyright (c) 2021, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef MCUFATFS_CARDPINS_CONFIG_H_
#define MCUFATFS_CARDPINS_CONFIG_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "McuLibconfig.h"
#include "McuGPIO.h"

/* card detect pin */
#ifndef McuFatFS_CONFIG_HAS_CARD_DETECT_PIN
  #define McuFatFS_CONFIG_HAS_CARD_DETECT_PIN (0)
    /*!< 1: has card detection pin. 0: no card detection pin */
#endif
#if McuFatFS_CONFIG_HAS_CARD_DETECT_PIN
  #ifndef McuFatFS_CONFIG_CARD_DETECT_GPIO
    #define McuFatFS_CONFIG_CARD_DETECT_GPIO            GPIOC
  #endif
  #ifndef McuFatFS_CONFIG_CARD_DETECT_PORT
    #define McuFatFS_CONFIG_CARD_DETECT_PORT            PORTC
  #endif
  #ifndef McuFatFS_CONFIG_CARD_DETECT_PIN
    #define McuFatFS_CONFIG_CARD_DETECT_PIN             0U
  #endif
  #ifndef McuFatFS_CONFIG_CARD_DETECT_PULL
    #define McuFatFS_CONFIG_CARD_DETECT_PULL            McuGPIO_PULL_DOWN
      /*!< type of pull, use McuGPIO_PULL_DISABLE for no pull resistor configuration */
  #endif
  #ifndef McuFatFS_CONFIG_CARD_DETECT_IOCON
    #define McuFatFS_CONFIG_CARD_DETECT_IOCON           /*IOCON_INDEX_PIO0_4*/
      /*!< For LPC Cortex-M0 only */
  #endif
#ifndef McuFatFS_CONFIG_CARD_DETECT_IS_HIGH_ACTIVE
  #define McuFatFS_CONFIG_CARD_DETECT_IS_HIGH_ACTIVE   (1)
    /*!< 1: pin is HIGH active for card present; 0: pin is LOW active if card is present */
#endif

#endif /* McuFatFS_CONFIG_HAS_CARD_DETECT_PIN */


/* write protection pin */
#ifndef McuFatFS_CONFIG_HAS_WRITE_PROTECT_PIN
  #define McuFatFS_CONFIG_HAS_WRITE_PROTECT_PIN (0)
    /*!< 1: has write protection pin. 0: no card write protection pin */
#endif
#if McuFatFS_CONFIG_HAS_WRITE_PROTECT_PIN
  #ifndef McuFatFS_CONFIG_WRITE_PROTECT_GPIO
    #define McuFatFS_CONFIG_WRITE_PROTECT_GPIO            GPIOC
  #endif
  #ifndef McuFatFS_CONFIG_WRITE_PROTECT_PORT
    #define McuFatFS_CONFIG_WRITE_PROTECT_PORT            PORTC
  #endif
  #ifndef McuFatFS_CONFIG_WRITE_PROTECT_PIN
    #define McuFatFS_CONFIG_WRITE_PROTECT_PIN             1U
  #endif
  #ifndef McuFatFS_CONFIG_WRITE_PROTECT_PULL
    #define McuFatFS_CONFIG_WRITE_PROTECT_PULL            McuGPIO_PULL_DOWN
      /*!< type of pull, use McuGPIO_PULL_DISABLE for no pull resistor configuration */
  #endif
  #ifndef McuFatFS_CONFIG_WRITE_PROTECT_IOCON
    #define McuFatFS_CONFIG_WRITE_PROTECT_IOCON           /*IOCON_INDEX_PIO0_5*/
      /*!< For LPC Cortex-M0 only */
  #endif
#ifndef McuFatFS_CONFIG_WRITE_PROTECT_IS_HIGH_ACTIVE
  #define McuFatFS_CONFIG_WRITE_PROTECT_IS_HIGH_ACTIVE    (1)
    /*!< 1: pin is HIGH active for write protection; 0: pin is LOW active if card is write protected */
#endif

#endif /* McuFatFS_CONFIG_HAS_WRITE_PROTECTION_PIN */


/* example configurations below: */
#if 0 /* tinyK22 */
  #define McuFatFS_CONFIG_HAS_CARD_DETECT_PIN           (1)
  #define McuFatFS_CONFIG_CARD_DETECT_GPIO              GPIOC
  #define McuFatFS_CONFIG_CARD_DETECT_PORT              PORTC
  #define McuFatFS_CONFIG_CARD_DETECT_PIN               0U
  #define McuFatFS_CONFIG_CARD_DETECT_PULL              McuGPIO_PULL_DOWN
  #define McuFatFS_CONFIG_CARD_DETECT_IS_HIGH_ACTIVE    (1)
  #define McuFatFS_CONFIG_HAS_WRITE_PROTECT_PIN         (0)
#elif 0 /* LPC55S16*/
  #define McuFatFS_CONFIG_HAS_CARD_DETECT_PIN           (1)
  #define McuFatFS_CONFIG_CARD_DETECT_GPIO              GPIO
  #define McuFatFS_CONFIG_CARD_DETECT_PORT              0
  #define McuFatFS_CONFIG_CARD_DETECT_PIN               16U
  #define McuFatFS_CONFIG_CARD_DETECT_PULL              McuGPIO_PULL_DISABLE /* https://www.pololu.com/product/2587 */
  #define McuFatFS_CONFIG_CARD_DETECT_IS_HIGH_ACTIVE    (1)  /*  https://www.pololu.com/product/2587 */
  #define McuFatFS_CONFIG_HAS_WRITE_PROTECT_PIN         (0)
#endif

#ifdef __cplusplus
}  /* extern "C" */
#endif

#endif /* MCUFATFS_CARDPINS_CONFIG_H_ */
