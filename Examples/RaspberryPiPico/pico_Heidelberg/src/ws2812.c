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
#define WS2812_USE_MULTIPLE_LANES (1 || NECO_NOF_LANES>1) /* if using multiple lanes or single lane */

static int sm = 0; /* state machine index. \todo should find a free SM */

#if WS2812_USE_MULTIPLE_LANES


#define DMA_CHANNEL         (0) /* bit plane content DMA channel */
#define DMA_CHANNEL_MASK    (1u << DMA_CHANNEL)
#define DMA_CHANNELS_MASK   (DMA_CHANNEL_MASK)

#define RESET_TIME_US     (100)  /* spec: 50 us. need to pause bit stream for this time at the end to latch the values into the LED */
static struct semaphore reset_delay_complete_sem; /* semaphore used to make a delay at the end of the transfer. Posted when it is safe to output a new set of values */
static alarm_id_t reset_delay_alarm_id; /*  alarm id handle for handling delay */

static int64_t reset_delay_complete(alarm_id_t id, void *user_data) {
  reset_delay_alarm_id = 0; /* reset alarm id */
  sem_release(&reset_delay_complete_sem); /* release semaphore */
  return 0; /* no repeat */
}

void /*__isr*/ dma_complete_handler(void) {
  if (dma_hw->ints0 & DMA_CHANNEL_MASK) {
    dma_hw->ints0 = DMA_CHANNEL_MASK; /* clear IRQ */
    /* when the DMA is complete we start the reset delay timer */
    if (reset_delay_alarm_id) {
      cancel_alarm(reset_delay_alarm_id);
    }
    reset_delay_alarm_id = add_alarm_in_us(RESET_TIME_US, reset_delay_complete, NULL, true);
  }
}

static void dma_init(PIO pio, uint sm) {
  dma_claim_mask(DMA_CHANNELS_MASK); /* check that the DMA channel we want is available */
  dma_channel_config channel_config = dma_channel_get_default_config(DMA_CHANNEL); /* get default configuration */
  channel_config_set_dreq(&channel_config, pio_get_dreq(pio, sm, true)); /* configure data request. true: sending data to the PIO state machine */
  channel_config_set_transfer_data_size(&channel_config, DMA_SIZE_32); /* data transfer size is 32 bits */
  channel_config_set_read_increment(&channel_config, true); /* each read of the data will increase the read pointer */
  dma_channel_configure(DMA_CHANNEL,
                        &channel_config,
                        &pio->txf[sm], /* write address: write to PIO FIFO */
                        NULL, /* don't provide a read address yet */
                        NEOC_NOF_LEDS_IN_LANE*NEO_NOF_BITS_PIXEL,/* number of transfers */
                        false); /* don't start yet */
  irq_set_exclusive_handler(DMA_IRQ_0, dma_complete_handler); /* after DMA all data, raise an interrupt */
  dma_channel_set_irq0_enabled(DMA_CHANNEL, true); /* map DMA channel to interrupt */
  irq_set_enabled(DMA_IRQ_0, true); /* enable interrupt */
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

const uint32_t pixel[NEOC_NOF_LEDS_IN_LANE*NEO_NOF_BITS_PIXEL] = {
    /* each value is a 32bit (max 32 lanes) of pixel values put out by the PIO */
    0x2, 0x2, 0x2, 0x2, 0x0, 0x0, 0x0, 0x1, /* g */
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x1, /* r */
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x1, 0x1, /* b */
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x1, /* w */
};
const uint32_t pixel0[NEOC_NOF_LEDS_IN_LANE*NEO_NOF_BITS_PIXEL] = {
    /* each value is a 32bit (max 32 lanes) of pixel values put out by the PIO */
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, /* g */
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, /* r */
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, /* b */
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, /* w */
};

const uint32_t pixel_g[] = { /* grbw order: bytes are processed LSB to MSB */
    0x00000000, 0x01000000, /* g */
    0x0, 0x00, /* r */
    0x0, 0x00, /* b */
    0x0, 0x00, /* w */
};

int WS2812_Transfer(uint8_t *data, size_t dataSize) {
#if WS2812_USE_MULTIPLE_LANES

  //pio_sm_put_blocking(pio0, sm, 0x11223311);
  for(int i=0; i<8; i++) {
    pio_sm_put_blocking(pio0, sm, pixel_g[i]);
  }
#if 0
  for(int i=0; i<NEOC_NOF_LEDS_IN_LANE*NEO_NOF_BITS_PIXEL; i++) {
    pio_sm_put_blocking(pio0, sm, pixel[i]);
  }
#endif
#if 0
  for(int i=0; i<NEOC_NOF_LEDS_IN_LANE*NEO_NOF_BITS_PIXEL; i++) {
    pio_sm_put_blocking(pio0, sm, pixel[i]);
  }
#endif
#if 0
  sem_acquire_blocking(&reset_delay_complete_sem); /* get semaphore */
  dma_channel_set_read_addr(DMA_CHANNEL, pixel0, true); /* trigger DMA transfer */
  sem_acquire_blocking(&reset_delay_complete_sem); /* get semaphore */
  dma_channel_set_read_addr(DMA_CHANNEL, pixel, true); /* trigger DMA transfer */
#endif
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
  ws2812_parallel_program_init(pio, sm, offset, NEOC_PIN_START, NEOC_NOF_LANES, 800000);
  sem_init(&reset_delay_complete_sem, 1, 1); /* semaphore initially posted so we don't block first time */
  dma_init(pio, sm);
#else /* single lane */
  uint offset = pio_add_program(pio, &ws2812_program);
  ws2812_program_init(pio, sm, offset, NEOC_PIN_START, 800000, NEOC_NOF_COLORS==4);
#endif
}

#endif /* PL_CONFIG_USE_NEO_PIXEL_HW */
