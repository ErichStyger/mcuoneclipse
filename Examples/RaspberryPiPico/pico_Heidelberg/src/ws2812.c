/*
 * Copyright (c) 2022, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "app_platform.h"
#if PL_CONFIG_USE_NEO_PIXEL_HW
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "NeoConfig.h"
#include "NeoPixel.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "ws2812.pio.h"
#include "ws2812.h"
#include "pico/stdlib.h"
#include "McuRTOS.h"
/* using multiple lanes: */
#include "hardware/dma.h"
#include "hardware/irq.h"
#include "pico/sem.h"

/* see https://www.raspberrypi.com/news/how-to-power-loads-of-leds-with-a-single-raspberry-pi-pico/ */
#define WS2812_USE_MULTIPLE_LANES (0 || NECO_NOF_LANES>1) /* if using multiple lanes or single lane */

static int sm = 0; /* state machine index. \todo should find a free SM */

#if WS2812_USE_MULTIPLE_LANES

#define FRAC_BITS 4

//#define VALUE_PLANE_COUNT (8+FRAC_BITS)
/* we store value (8 bits + fractional bits of a single color (R/G/B/W) value) for multiple
 * strings, in bit planes. bit plane N has the Nth bit of each string. */
//typedef struct {
//  uint32_t planes[VALUE_PLANE_COUNT]; /* stored MSB first */
//} value_bits_t;

/* bit plane content DMA channel */
#define DMA_CHANNEL 0
/* chain channel for configuring main DMA channel to output from disjoint 8 word fragments of memory */
#define DMA_CB_CHANNEL 1

#define DMA_CHANNEL_MASK (1u << DMA_CHANNEL)
#define DMA_CB_CHANNEL_MASK (1u << DMA_CB_CHANNEL)
#define DMA_CHANNELS_MASK (DMA_CHANNEL_MASK | DMA_CB_CHANNEL_MASK)

static uintptr_t fragment_start[NEOC_NOF_LEDS_IN_LANE*4 + 1]; /* start of each value fragment (+1 for NULL terminator) */

static struct semaphore reset_delay_complete_sem; /* posted when it is safe to output a new set of values */

static alarm_id_t reset_delay_alarm_id; /*  alarm handle for handling delay */

static int64_t reset_delay_complete(alarm_id_t id, void *user_data) {
  reset_delay_alarm_id = 0;
  sem_release(&reset_delay_complete_sem);
  /* no repeat */
  return 0;
}

void __isr dma_complete_handler(void) {
  if (dma_hw->ints0 & DMA_CHANNEL_MASK) {
    /* clear IRQ */
    dma_hw->ints0 = DMA_CHANNEL_MASK;
    /* when the DMA is complete we start the reset delay timer */
    if (reset_delay_alarm_id) {
      cancel_alarm(reset_delay_alarm_id);
    }
    reset_delay_alarm_id = add_alarm_in_us(400, reset_delay_complete, NULL, true);
  }
}

static void dma_init(PIO pio, uint sm) {
  dma_claim_mask(DMA_CHANNELS_MASK);

  /* main DMA channel outputs 8 word fragments, and then chains back to the chain channel */
  dma_channel_config channel_config = dma_channel_get_default_config(DMA_CHANNEL);
  channel_config_set_dreq(&channel_config, pio_get_dreq(pio, sm, true));
  channel_config_set_chain_to(&channel_config, DMA_CB_CHANNEL);
  channel_config_set_irq_quiet(&channel_config, true);
  dma_channel_configure(DMA_CHANNEL,
                        &channel_config,
                        &pio->txf[sm], /* write address */
                        NULL, /* don't provide a read address yet */
                        8, /* number of transfers: 8 words for 8 bit planes */
                        false); /* don't start yet */

  /* chain channel sends single word pointer to start of fragment each time */
  dma_channel_config chain_config = dma_channel_get_default_config(DMA_CB_CHANNEL);
  dma_channel_configure(DMA_CB_CHANNEL,
                        &chain_config,
                        &dma_channel_hw_addr(
                                DMA_CHANNEL)->al3_read_addr_trig,  // ch DMA config (target "ring" buffer size 4) - this is (read_addr trigger)
                        NULL, // set later
                        1, /* number of transfers */
                        false); /* don't start yet */

  irq_set_exclusive_handler(DMA_IRQ_0, dma_complete_handler);
  dma_channel_set_irq0_enabled(DMA_CHANNEL, true);
  irq_set_enabled(DMA_IRQ_0, true);
}

#endif /* WS2812_USE_MULTIPLE_LANES */

#if !WS2812_USE_MULTIPLE_LANES
static inline void put_pixel_rgb(uint32_t pixel_grb) {
  pio_sm_put_blocking(pio0, sm, pixel_grb<<8u);
}

static inline void put_pixel_wrgb(uint32_t pixel_grbw) { /* data is sent grbw */
  pio_sm_put_blocking(pio0, sm, pixel_grbw);
}

static inline uint32_t urgb_u32(uint8_t r, uint8_t g, uint8_t b) { /* data is sent grb */
  return (((uint32_t)(g)<<16) | (uint32_t)(r)<<8) | (uint32_t)(b);
}

static inline uint32_t uwrgb_u32(uint8_t w, uint8_t r, uint8_t g, uint8_t b) {
  return ((uint32_t)(g) << 24) | ((uint32_t)(r) << 16) | ((uint32_t)(b)<<8) | (uint32_t)(w);
}
#endif

const uint8_t pixel[] = {
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, /* g */
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, /* r */
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x1, 0x1, /* b */
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, /* w */
};

int WS2812_Transfer(uint8_t *data, size_t dataSize) {
#if WS2812_USE_MULTIPLE_LANES

  for(int i=0; i<sizeof(pixel); i++) {
    pio_sm_put_blocking(pio0, sm, pixel[i]);
  }
#if 0
  /* LSB is channel 0 (GPIO2) */
  pio_sm_put_blocking(pio0, sm, 0xAfffffff);
  pio_sm_put_blocking(pio0, sm, 0xBfffffff);
  pio_sm_put_blocking(pio0, sm, 0xCfffffff);
  pio_sm_put_blocking(pio0, sm, 0xDfffffff);
  pio_sm_put_blocking(pio0, sm, 0xEfffffff);
  pio_sm_put_blocking(pio0, sm, 0xfffffff1);
  pio_sm_put_blocking(pio0, sm, 0xfffffff2);
  pio_sm_put_blocking(pio0, sm, 0xfffffff3);
  pio_sm_put_blocking(pio0, sm, 0b0);
  pio_sm_put_blocking(pio0, sm, 0b1);
  pio_sm_put_blocking(pio0, sm, 0b1);
  pio_sm_put_blocking(pio0, sm, 0b0);
  pio_sm_put_blocking(pio0, sm, 0b0);
  pio_sm_put_blocking(pio0, sm, 0b1);
#endif
  sem_acquire_blocking(&reset_delay_complete_sem); /* get semaphore */
  dma_channel_set_read_addr(DMA_CB_CHANNEL, data, true);
#else
  uint8_t r, g, b;

  for(int i=0; i<NEOC_NOF_PIXEL; i++) {
  #if NEOC_NOF_COLORS==3
    NEO_GetPixelRGB(0, i, &r, &g, &b);
    put_pixel_rgb(urgb_u32(r, g, b)); /* use the PIO to shift out the 24bits (grb) of the 32bit value passed, with MSB first */
  #elif NEOC_NOF_COLORS==4
    uint8_t w;

    NEO_GetPixelWRGB(NEOC_LANE_START, i, &w, &r, &g, &b);
    put_pixel_wrgb(uwrgb_u32(w, r, g, b)); /* use the PIO to shift out 32bits (grbw) of the 32bit value passed, with MSB first */
  #endif
  }
  vTaskDelay(pdMS_TO_TICKS(10)); /* latch */
#endif
  return 0; /* ok */
}

void WS2812_Init(void) {
  PIO pio = pio0; /* the PIO used. \todo: find free PIO */
  sm = 0; /* could be local? */
#if WS2812_USE_MULTIPLE_LANES
  uint offset = pio_add_program(pio, &ws2812_parallel_program);
  ws2812_parallel_program_init(pio, sm, offset, NEOC_PIN_START, NECO_NOF_LANES, 800000);
  sem_init(&reset_delay_complete_sem, 1, 1); /* initially posted so we don't block first time */
  dma_init(pio, sm);
#else /* single lane */
  uint offset = pio_add_program(pio, &ws2812_program);
  ws2812_program_init(pio, sm, offset, NEOC_PIN_START, 800000, NEOC_NOF_COLORS==4);
#endif
}

#endif /* PL_CONFIG_USE_NEO_PIXEL_HW */
