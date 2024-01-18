/*
 * Copyright (c) 2019-2022, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef MCUI2CLIB_H_
#define MCUI2CLIB_H_

#include <stdint.h>
#include "McuI2cLibconfig.h"

typedef enum McuI2cLib_EnumStartFlags_ {
  MCUI2CLIB_SEND_START,        /* Start is sent */
  MCUI2CLIB_DO_NOT_SEND_START  /* Start is not sent */
} McuI2cLib_EnumStartFlags;

typedef enum I2CLIB_EnumAckFlags_ {
  MCUI2CLIB_SEND_LAST_ACK,   /* Nack after last received byte is sent */
  MCUI2CLIB_DO_NOT_LAST_ACK  /* Nack after last received byte is not sent */
} McuI2cLib_EnumAckFlags;

uint8_t McuI2cLib_RecvBlockCustom(void *Ptr, uint16_t Siz, uint16_t *Rcv, McuI2cLib_EnumStartFlags flagsStart, McuI2cLib_EnumAckFlags flagsAck);

uint8_t McuI2cLib_RecvBlock(void *Ptr, uint16_t Siz, uint16_t *Rcv);
uint8_t McuI2cLib_SendBlock(void *Ptr, uint16_t Siz, uint16_t *Snt);
uint8_t McuI2cLib_SendBlockContinue(void *Ptr, uint16_t Siz, uint16_t *Snt);
uint8_t McuI2cLib_SendStop(void);
uint8_t McuI2cLib_SelectSlave(uint8_t Slv);

uint8_t McuI2cLib_ReadAddress(uint8_t i2cAddr, uint8_t *memAddr, uint8_t memAddrSize, uint8_t *data, uint16_t dataSize);
uint8_t McuI2cLib_WriteAddress(uint8_t i2cAddr, uint8_t *memAddr, uint8_t memAddrSize, uint8_t *data, uint16_t dataSize);

void McuI2cLib_Deinit(void);
void McuI2cLib_Init(void);

#endif /* MCUI2CLIB_H_ */
