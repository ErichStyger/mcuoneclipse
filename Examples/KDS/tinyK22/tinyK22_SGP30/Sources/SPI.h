/*
 * SPI.h
 *
 *  Created on: 10.12.2014
 *      Author: Erich Styger
 */

#ifndef SPI_H_
#define SPI_H_

typedef enum { /* must match index values in SPI component for given speed */
  SPI_BAUD_INDEX_SSD1351  = 0 /* 8.5 MHz */,
  SPI_BAUD_INDEX_SD_SLOW  = 1 /* 375 kHz */,
  SPI_BAUD_INDEX_SD_FAST  = 2 /* 1.5 MHz */,
} SPI_BaudIndex;

/*!
 * \brief Event hook called before activating/accessing the SPI bus
 */
void SPI_OnSPIActivate(SPI_BaudIndex idx);

/*!
 * \brief Event hook called after activating/accessing the SPI bus
 */
void SPI_OnSPIDeactivate(SPI_BaudIndex idx);

/*!
 * \brief Driver initialization.
 */
void SPI_Init(void);

/*!
 * \brief Driver deinitalization
 */
void SPI_Deinit(void);


#endif /* SPI_H_ */
