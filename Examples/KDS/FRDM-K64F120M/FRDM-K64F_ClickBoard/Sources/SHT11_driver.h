/*
 * SHT11_driver.h
 *
 *  Created on: 06.03.2015
 *      Author: tastyger
 */

#ifndef SHT11_DRIVER_H_
#define SHT11_DRIVER_H_

/*!
 * \brief Reads the temperature and humidity values from the sensor.
 * \param fT Pointer where to store the temperature.
 * \param fRH Pointer where to store the humidity.
 * \return Error code, ERR_OK if everything is ok.
 */
uint8_t SHT11_Read(float *fT, float *fRH);

/*!
 * \brief Performs a softreset of the device
 * \return Error code, ERR_OK if everything is ok.
 */
uint8_t SHT11_SoftReset(void);

#endif /* SHT11_DRIVER_H_ */
