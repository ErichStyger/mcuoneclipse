/**
 * \file
 * \brief Configuration header file for SDK_BitIO
 * Copyright (c) 2020, Erich Styger
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * This header file is used to configure settings of the SDK Bit I/O module.
 */

#ifndef __McuSDKBitIO_CONFIG_H
#define __McuSDKBitIO_CONFIG_H

#ifndef McuSDKBitIO_CONFIG_DO_PIN_MUXING
  #define McuSDKBitIO_CONFIG_DO_PIN_MUXING  0  /* 1: perform pin muxing in Init(), 0: do not do pin muxing */
#endif

#endif /* __McuSDKBitIO_CONFIG_H */
