/**
 * \file
 * \brief Interface to the DAC on the PRG_G board.
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * This module implements the DAC (Digital to Digital Converter) driver.
 */

#ifndef SRC_DAC_H_
#define SRC_DAC_H_

#include <stdint.h>

/** @addtogroup DAC
  * @{
  */

/*!
 * \brief Starts the DAC
 */
void DAC_Start(void);

/*!
 * \brief Sets the DAC to produce a voltage. Must call DAC_Start() first.
 * \param mv milli-volt value to set
 */
void DAC_SetMilliVolt(uint16_t mv);

/*!
 * \brief Stops the DAC started with DAC_Start().
 */
void DAC_Stop(void);

/*!
 * \brief DAC Driver initialization.
 */
void DAC_Init(void);

/**
  * @}
  */

#endif /* SRC_DAC_H_ */
