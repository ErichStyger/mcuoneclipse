/*
 * vl53l0x.h
 */

#ifndef SOURCES_VL53L0X_H_
#define SOURCES_VL53L0X_H_

#include <stdint.h>


/*!
 * \brief Performs a single shot measurement and returns the distance in millimeters
 * \return ERR_OK if everything is fine, error code otherwise
 */
uint8_t VL53L0X_MeasureSingle(uint16_t *mm);

/*!
 * \brief Initialize the sensor with the default settings.
 * \return ERR_OK if everything is fine, error code otherwise
 */
uint8_t VL53L0X_Init(void);


#endif /* SOURCES_VL53L0X_H_ */
