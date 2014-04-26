/*
 * SPI.h
 *
 *  Created on: Apr 23, 2014
 *      Author: tastyger
 */

#ifndef SPI_H_
#define SPI_H_

void SPI_RequestSPIBus(void);

void SPI_ReleaseSPIBus(void);

void SPI_OnBlockReceived(LDD_TUserData *UserDataPtr);

void SPI_WriteByte(unsigned char write);

uint8_t SPI_ReadByte(void);

void SPI_Init(void);

#endif /* SPI_H_ */
