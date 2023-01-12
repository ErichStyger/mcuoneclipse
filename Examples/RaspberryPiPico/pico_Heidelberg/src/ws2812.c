/*
 * Copyright (c) 2022, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "app_platform.h"
#if PL_CONFIG_USE_NEO_PIXEL_HW
#include <stdio.h>
#include <stdlib.h>
#include "NeoConfig.h"
#include "NeoPixel.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "ws2812.pio.h"
#include "ws2812.h"
#include "pico/stdlib.h"
#include "McuRTOS.h"

#define WS2812_IS_RGBW      (NEOC_NOF_COLORS==4)
#define WS2812_PIN          NEOC_LANE_START
static int sm = 0; /* \todo should fine a free SM */

static inline void put_pixel_rgb(uint32_t pixel_grb) {
  pio_sm_put_blocking(pio0, sm, pixel_grb << 8u);
}

static inline void put_pixel_wrgb(uint32_t pixel_wgrb) {
  pio_sm_put_blocking(pio0, sm, pixel_wgrb);
}

static inline uint32_t urgb_u32(uint8_t r, uint8_t g, uint8_t b) {
  return ((uint32_t) (r) << 8) | ((uint32_t) (g) << 16) |  (uint32_t) (b);
}

static inline uint32_t uwrgb_u32(uint8_t w, uint8_t r, uint8_t g, uint8_t b) {
  return ((uint32_t)(r) << 16) |  ((uint32_t)(g) << 24) |  ((uint32_t)(b)<<8) | (uint32_t)(w);
}

int WS2812_Transfer(void) {
  uint8_t r, g, b;

  for(int i=0; i<NEOC_NOF_PIXEL; i++) {
#if NEOC_NOF_COLORS==3
    NEO_GetPixelRGB(0, i, &r, &g, &b);
    put_pixel_rgb(urgb_u32(r, g, b));
#elif NEOC_NOF_COLORS==4
    uint8_t w;

    NEO_GetPixelWRGB(NEOC_LANE_START, i, &w, &r, &g, &b);
    put_pixel_wrgb(uwrgb_u32(w, r, g, b));
#endif
  }
  //sleep_ms(10); /* latch */
  vTaskDelay(pdMS_TO_TICKS(10)); /* latch */
  return 0;
}

void WS2812_Init(void) {
  PIO pio = pio0;
  uint offset = pio_add_program(pio, &ws2812_program);
  ws2812_program_init(pio, sm, offset, WS2812_PIN, 800000, WS2812_IS_RGBW);
}

#endif /* PL_CONFIG_USE_NEO_PIXEL_HW */
