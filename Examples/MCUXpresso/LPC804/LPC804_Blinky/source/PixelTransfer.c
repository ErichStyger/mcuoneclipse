/*
 * Copyright (c) 2021, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "McuLib.h"
#include "PixelTransfer.h"
#include "ws2812b.h"

uint8_t PIXELTRANS_Send(uint8_t *data, size_t dataSize) {
  WS2812B_SendPixels(data, dataSize);
  return ERR_OK;
}
