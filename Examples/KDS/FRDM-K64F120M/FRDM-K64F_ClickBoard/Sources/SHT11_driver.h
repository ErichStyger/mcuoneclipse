/*
 * SHT11_driver.h
 *
 *  Created on: 06.03.2015
 *      Author: tastyger
 */

#ifndef SHT11_DRIVER_H_
#define SHT11_DRIVER_H_

void Read_SHT11(float *fT, float *fRH);

uint8_t s_softreset(void);

#endif /* SHT11_DRIVER_H_ */
