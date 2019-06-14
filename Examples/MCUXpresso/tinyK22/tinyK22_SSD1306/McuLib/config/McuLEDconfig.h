/*
 * Copyright (c) 2019, Erich Styger
 * All rights reserved.
 *
 * Configuration header file for McuLED
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef MCULED_CONFIG_H_
#define MCULED_CONFIG_H_

#ifdef __cplusplus
extern "C" {
#endif

#define MCULED_USE_DYNAMIC_MEMORY    (1)

#if !MCULED_USE_DYNAMIC_MEMORY
  #define MCULED_CONFIG_MAX_NOF_LEDS  (5)
#endif

#ifdef __cplusplus
}  /* extern "C" */
#endif

#endif /* MCULEDCONFIG_H_ */
