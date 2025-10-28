/*
 * Copyright (c) 2023, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef MY_LEDS_H_
#define MY_LEDS_H_

#include "McuLib.h"
#include "leds_config.h"
#include <stdint.h>
#include <stdbool.h>
#include "McuShell.h"

#ifdef __cplusplus
extern "C" {
#endif

/*!
 * \brief Command line handler
 * \param cmd String to command to be parsed
 * \param handled Returns if command has been handled
 * \param io I/O channel
 * \return Error code, ERR_OK if everything is ok
 */
uint8_t Leds_ParseCommand(const uint8_t *cmd, bool *handled, McuShell_ConstStdIOType *io);

/*!
 * handles for the different LEDs
 */
typedef enum LEDS_Leds_e {
#if LEDS_CONFIG_HAS_RED_LED
  LEDS_RED,      /*!< red LED */
#endif
#if LEDS_CONFIG_HAS_GREEN_LED
  LEDS_GREEN,    /*!< green LED */
#endif
#if LEDS_CONFIG_HAS_BLUE_LED
  LEDS_BLUE,     /*!< blue LED */
#endif
#if LEDS_CONFIG_HAS_ORANGE_LED
  LEDS_ORANGE,   /*!< orange LED */
#endif
#if LEDS_CONFIG_HAS_BLUE_TINY_LED
  LEDS_TINY_BLUE, /*!< blue LED on tinyK22 board */
#endif
#if LEDS_CONFIG_HAS_GREEN_PICO_LED
  LEDS_PICO_GREEN, /*!< greem LED on Pico board */
#endif
  LEDS_NOF_LEDS, /*!< Sentinel, must be last! */
} LEDS_Leds_e;

/*!
 * \brief Turn LED on
 * \param led LED handle
 */
void Leds_On(LEDS_Leds_e led);

/*!
 * \brief Turn LED off
 * \param led LED handle
 */
void Leds_Off(LEDS_Leds_e led);

/*!
 * \brief Toggle LED
 * \param led LED handle
 */
void Leds_Neg(LEDS_Leds_e led);

/*!
 * \brief Module initialization, call it to initialize the driver
 */
void Leds_Init(void);

/*!
 * \brief Module de-initialization, call it to de-initialize the driver
 */
void Leds_Deinit(void);

#ifdef __cplusplus
}  /* extern "C" */
#endif

#endif /* MY_LEDS_H_ */
