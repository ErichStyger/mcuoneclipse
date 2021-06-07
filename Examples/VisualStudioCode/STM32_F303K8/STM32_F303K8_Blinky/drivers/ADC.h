/**
 * \file
 * \brief Implementation of the ADC on the PRG_G board.
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * This module implements the ADC (Analog to Digital Converter) driver.
 */

#ifndef SRC_ADC_H_
#define SRC_ADC_H_

#include <stdint.h>

/** @addtogroup ADC
  * @{
  */

/** \brief Selection of sensors */
typedef enum {
  ADC_LIGHT_SENSOR, /**< Light sensor */
  ADC_HALL_SENSOR   /**< Hall sensor */
} ADC_SensorE;

/*!
 * \brief Returns the measured voltage of the ADC in milli-Volts
 * \param sensor sensor to measure
 * \return milli-volts of the sensor
 */
uint32_t ADC_GetMilliVoltage(ADC_SensorE sensor);

/*!
 * \brief Initializes the ADC driver
 */
void ADC_Init(void);

/**
  * @}
  */

#endif /* SRC_ADC_H_ */
