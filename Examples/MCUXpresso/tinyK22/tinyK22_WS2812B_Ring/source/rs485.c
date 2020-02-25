/*
 * Copyright (c) 2020, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#if PL_CONFIG_USE_RS485
#include "rs485.h"
#include "McuGPIO.h"

/* DE, TxEnable, RTS: PTB19: high active */
#define RS485_TX_EN_GPIO       GPIOB
#define RS485_TX_EN_PORT       PORTB
#define RS485_TX_EN_PIN        19U

static McuGPIO_Handle_t RS485_TxEn;

void RS485_RxEnable(void) {
  McuGPIO_SetLow(RS485_TxEn);
}

void RS485_TxEnable(void) {
  McuGPIO_SetHigh(RS485_TxEn);
}

void RS485_Deinit(void) {
  RS485_TxEn = McuGPIO_DeinitGPIO(RS485_TxEn);
}

void RS485_Init(void) {
  McuGPIO_Config_t config;

  McuGPIO_GetDefaultConfig(&config);

  config.hw.gpio  = RS485_TX_EN_GPIO;
  config.hw.port  = RS485_TX_EN_PORT;
  config.hw.pin   = RS485_TX_EN_PIN;
  config.isInput = false;
  config.isHighOnInit = false; /* Tx disabled */
  RS485_TxEn = McuGPIO_InitGPIO(&config);

  RS485_RxEnable();
}

#endif /* PL_CONFIG_USE_RS485 */
