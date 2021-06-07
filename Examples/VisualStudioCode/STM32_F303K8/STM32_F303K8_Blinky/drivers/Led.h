/**
 * \file
 * \brief Interface to the LEDs on the PRG_G board.
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * This module implements functions for the LEDs.
 */

#ifndef SRC_LED_H_
#define SRC_LED_H_

#include <stdbool.h>

/** @addtogroup LED
  * @{
  */

/*!
 * \brief Identifiers for the LEDs on the board
 */
typedef enum {
  LED_LED0, /*!< LED0 is the green LED on the STM32 Nucleo board */
  LED_LED1, /*!< LED1 is on the extension board */
  LED_LED2, /*!< LED2 is on the extension board */
  LED_LED3, /*!< LED3 is on the extension board */
  LED_LED4, /*!< LED4 is on the extension board */
  LED_LEDR, /*!< Red RGB LED */
  LED_LEDG, /*!< Green RGB LED */
  LED_LEDB, /*!< Blue RGB LED */
} LED_LedId;

/*!
 * \brief Turns a LED on
 * \param led ID of the LED
 */
void LED_On(LED_LedId led);

/*!
 * \brief Turns a LED off
 * \param led ID of the LED
 */
void LED_Off(LED_LedId led);

/*!
 * \brief Toggles or negates a LED
 * \param led ID of the LED
 */
void LED_Neg(LED_LedId led);

/*!
 * \brief Returns the status of a LED
 * \param led ID of the LED
 * \return true if LED is on, false if LED is off
 */
bool LED_Get(LED_LedId led);

/*!
 * \brief Turns a LED on or off based on parameter
 * \param led ID of the LED
 * \param on if LED is on or off
 */
void LED_Put(LED_LedId led, bool on);

/*!
 * \brief LED initialization.
 */
void LED_Init(void);

/**
  * @}
  */
#endif /* SRC_LED_H_ */
