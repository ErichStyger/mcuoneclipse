/**
 *\file
 *\brief Interface for a AT25DF641 64MBit flash chip, to communicate with SPI.
 *\author Andreas Schoepfer andreas.schoepfer@stud.hslu.ch
 *\date 05.12.11
 *  
 */
#ifndef __FLASHEXT_H
#define __FLASHEXT_H

#include "PE_Types.h"

uint8_t FLASH_ReadStatusReg(uint8_t* statusReg);

uint8_t FLASH_ReadByte(uint32_t addr, uint8_t* data);

uint8_t FLASH_WriteByte(uint32_t addr, uint8_t* data);

void FLASH_Init(void);

#endif /* FLASHEXT_H_ */
