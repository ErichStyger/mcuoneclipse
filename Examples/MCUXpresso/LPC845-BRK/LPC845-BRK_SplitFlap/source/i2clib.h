/*
 * Copyright (c) 2019, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef I2CLIB_H_
#define I2CLIB_H_

#include <stdint.h>

typedef enum I2CLIB_EnumStartFlags_ {
  I2CLIB_SEND_START,        /* Start is sent */
  I2CLIB_DO_NOT_SEND_START  /* Start is not sent */
} I2CLIB_EnumStartFlags;

typedef enum I2CLIB_EnumAckFlags_ {
  I2CLIB_SEND_LAST_ACK,   /* Nack after last received byte is sent */
  I2CLIB_DO_NOT_LAST_ACK  /* Nack after last received byte is not sent */
} I2CLIB_EnumAckFlags;

uint8_t I2CLIB_RecvBlockCustom(void *Ptr, uint16_t Siz, uint16_t *Rcv, I2CLIB_EnumStartFlags flagsStart, I2CLIB_EnumAckFlags flagsAck);

uint8_t I2CLIB_RecvBlock(void *Ptr, uint16_t Siz, uint16_t *Rcv);
uint8_t I2CLIB_SendBlock(void *Ptr, uint16_t Siz, uint16_t *Snt);
uint8_t I2CLIB_SendBlockContinue(void *Ptr, uint16_t Siz, uint16_t *Snt);
uint8_t I2CLIB_SendStop(void);
uint8_t I2CLIB_SelectSlave(uint8_t Slv);

uint8_t I2CLIB_ReadAddress(uint8_t i2cAddr, uint8_t *memAddr, uint8_t memAddrSize, uint8_t *data, uint16_t dataSize);
uint8_t I2CLIB_WriteAddress(uint8_t i2cAddr, uint8_t *memAddr, uint8_t memAddrSize, uint8_t *data, uint16_t dataSize);

void I2CLIB_Init(void);

#endif /* I2CLIB_H_ */
