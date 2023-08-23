/*
 * Copyright (c) 2023, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef MCUST7735_CONFIG_H_
#define MCUST7735_CONFIG_H_

/* different display types supported */
#define MCUST7735_TYPE_128X128      (1)
#define MCUST7735_TYPE_160X80       (2)
#define MCUST7735_TYPE_160X128      (3)

#ifndef McuST7735_CONFIG_DISPLAY_TYPE
  #define McuST7735_CONFIG_DISPLAY_TYPE   MCUST7735_TYPE_128X128
#endif

#ifndef McuST7735_CONFIG_IS_ENABLED
  #define McuST7735_CONFIG_IS_ENABLED   (0)
    /*!< 1: driver is enabled. 0: driver is not enabled */
#endif

/* CS pin */
#ifndef McuST7735_CONFIG_CS_PIN_GPIO
  #define McuST7735_CONFIG_CS_PIN_GPIO   GPIOB
    /*!< GPIO for CS Pin */
#endif

#ifndef McuST7735_CONFIG_CS_PIN_PORT
  #define McuST7735_CONFIG_CS_PIN_PORT   PORTB
    /*!< PORT for CS Pin */
#endif

#ifndef McuST7735_CONFIG_CS_PIN_NUMBER
  #define McuST7735_CONFIG_CS_PIN_NUMBER   0
    /*!< Pin number of the CS Pin */
#endif

/* DC pin */
#ifndef McuST7735_CONFIG_DC_PIN_GPIO
  #define McuST7735_CONFIG_DC_PIN_GPIO   GPIOB
    /*!< GPIO for DC Pin */
#endif

#ifndef McuST7735_CONFIG_DC_PIN_PORT
  #define McuST7735_CONFIG_DC_PIN_PORT   PORTB
    /*!< PORT for DC Pin */
#endif

#ifndef McuST7735_CONFIG_DC_PIN_NUMBER
  #define McuST7735_CONFIG_DC_PIN_NUMBER   1
    /*!< Pin number of the DC Pin */
#endif

/* RESET pin */
#ifndef McuST7735_CONFIG_RESET_PIN_GPIO
  #define McuST7735_CONFIG_RESET_PIN_GPIO   GPIOB
    /*!< GPIO for CS Pin */
#endif

#ifndef McuST7735_CONFIG_RESET_PIN_PORT
  #define McuST7735_CONFIG_RESET_PIN_PORT   PORTB
    /*!< PORT for CS Pin */
#endif

#ifndef McuST7735_CONFIG_RESET_PIN_NUMBER
  #define McuST7735_CONFIG_RESET_PIN_NUMBER   2
    /*!< Pin number of the CSN Pin */
#endif


#endif /* MCUST7735_CONFIG_H_ */
