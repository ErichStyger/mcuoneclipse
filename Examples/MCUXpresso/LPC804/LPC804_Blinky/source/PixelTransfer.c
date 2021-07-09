/*
 * Copyright (c) 2021, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "McuLib.h"
#include "PixelTransfer.h"
#include "ws2812b.h"
#include "McuRTOS.h"

uint8_t PIXELTRANS_Send(uint8_t *data, size_t dataSize) {
  taskDISABLE_INTERRUPTS();
  WS2812B_SendPixels(data, dataSize);
  taskENABLE_INTERRUPTS();
  return ERR_OK;
}
