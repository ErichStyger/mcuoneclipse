/**
 * \file
 * \brief Interface to the pins on the PRG_G board.
 * \author Erich Styger, erich.styger@hslu.ch
 * This module implements the functions to use the GPIO pins.
 */

#ifndef BOARD_PIN_H_
#define BOARD_PIN_H_

#include <stdbool.h>

/** @addtogroup Pin
  * @{
  */

/*!
 * \brief Identifiers for the Pins on the board
 */
typedef enum {
  PIN_S1, /*!< Switch S1 */
  PIN_S2, /*!< Switch S2 */
  PIN_S3, /*!< Push button S3 */
  PIN_S4, /*!< Push button S4 */
  PIN_S5, /*!< Push button S5 */
  PIN_S6, /*!< Push button S6 */
  PIN_TILT, /*!< Tilt switch */
} Pin_PinId;

/*!
 * \brief Function used to check if a pin is high or low.
 * \param pin Pin to be used
 * \return true if the pin has a high level, false otherwise
 */
bool PIN_IsPinHigh(Pin_PinId pin);

/*!
 * \brief Pin driver initialization routine
 */
void PIN_Init(void);

/**
  * @}
  */

#endif /* BOARD_PIN_H_ */
