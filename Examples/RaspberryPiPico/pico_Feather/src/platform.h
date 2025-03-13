/*
 * Copyright (c) 2022-2025, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef PLATFORM_BOARD_H_

#ifdef __cplusplus
extern "C" {
#endif

#define PL_CONFIG_USE_SHELL           (1)
#define PL_CONFIG_USE_TUD_CDC         (1)

#define PL_CONFIG_USE_RTT             (0)
#define PL_CONFIG_USE_WIFI            (0)
#define PL_CONFIG_USE_PICO_W          (0)
#define PL_CONFIG_USE_NEO_PIXEL_HW    (0) /* if we have NeoPixels/SK6812 */
#define PL_CONFIG_USE_BUTTONS         (0)
#define PL_CONFIG_USE_MININI          (0)
#define PL_CONFIG_USE_NVMC            (0)

void PL_Init(void);
void PL_Deinit(void);

#ifdef __cplusplus
}  /* extern "C" */
#endif

#endif /* PLATFORM_BOARD_H_ */
