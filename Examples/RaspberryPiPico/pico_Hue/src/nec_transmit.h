/**
 * Copyright (c) 2021 mjcross
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pico/stdlib.h"
#include "hardware/pio.h"

#ifndef NEC_TRANSMIT_H__
#define NEC_TRANSMIT_H__
// public API

int nec_tx_init(PIO pio, uint pin);
uint32_t nec_encode_frame(uint8_t address, uint8_t data);

#endif /* NEC_TRANSMIT_H__ */
