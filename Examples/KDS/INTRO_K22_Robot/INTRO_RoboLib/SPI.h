/*
 * SPI.h
 *
 *  Created on: 10.12.2014
 *      Author: tastyger
 */

#ifndef SPI_H_
#define SPI_H_

typedef enum {
  SPI_BAUD_INDEX_SD_SLOW  = 0 /* 375 kHz */,
  SPI_BAUD_INDEX_SD_FAST  = 1 /* 12 MHz */,
  SPI_BAUD_INDEX_VS1053   = 2 /* 2.75 MHz */,
  SPI_BAUD_INDEX_NRF      = 3 /* 10 MHz */
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
