/*
 * Copyright (c) 2022, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
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

/* timing (+/-150ns):
 * 0: 400ns high, followed by 850ns low
 * 1: 850ns low,  followed by 400ns low
 */

#define WS2812_USE_MULTIPLE_LANES     (NEOC_NOF_LANES>1) /* if using multiple lanes or single lane */

static int sm = 0; /* state machine index. \todo should find a free SM */

#if NEOC_USE_DMA

#define DMA_CHANNEL         (0) /* bit plane content DMA channel */
#define DMA_CHANNEL_MASK    (1u<<DMA_CHANNEL)

#define RESET_TIME_US       (60)  /* RES time, specification says it needs at least 50 us. Need to pause bit stream for this time at the end to latch the values into the LED */

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
  dma_claim_mask(DMA_CHANNEL_MASK); /* check that the DMA channel we want is available */
  dma_channel_config channel_config = dma_channel_get_default_config(DMA_CHANNEL); /* get default configuration */
  channel_config_set_dreq(&channel_config, pio_get_dreq(pio, sm, true)); /* configure data request. true: sending data to the PIO state machine */
  channel_config_set_transfer_data_size(&channel_config, DMA_SIZE_32); /* data transfer size is 32 bits */
  channel_config_set_read_increment(&channel_config, true); /* each read of the data will increase the read pointer */
  dma_channel_configure(DMA_CHANNEL,
                        &channel_config,
                        &pio->txf[sm], /* write address: write to PIO FIFO */
                        NULL, /* don't provide a read address yet */
                    #if WS2812_USE_MULTIPLE_LANES
                        NEOC_NOF_LEDS_IN_LANE*2*NEOC_NOF_COLORS, /* number of transfers */
                    #else
                        NEOC_NOF_LEDS_IN_LANE, /* number of transfers */
                    #endif
                        false); /* don't start yet */
  irq_set_exclusive_handler(DMA_IRQ_0, dma_complete_handler); /* after DMA all data, raise an interrupt */
  dma_channel_set_irq0_enabled(DMA_CHANNEL, true); /* map DMA channel to interrupt */
  irq_set_enabled(DMA_IRQ_0, true); /* enable interrupt */
}
#endif /* NEOC_USE_DMA */

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

int WS2812_Transfer(uint32_t address, size_t nofBytes) {
#if WS2812_USE_MULTIPLE_LANES
  #if NEOC_USE_DMA
    sem_acquire_blocking(&reset_delay_complete_sem); /* get semaphore */
    dma_channel_set_read_addr(DMA_CHANNEL, (void*)address, true); /* trigger DMA transfer */
  #else
    uint32_t *p = (uint32_t*)address;
    for(int i=0; i<nofBytes/sizeof(uint32_t); i++) { /* without DMA: writing one after each other */
      pio_sm_put_blocking(pio0, sm, *p);
      p++;
    }
    vTaskDelay(pdMS_TO_TICKS(10)); /* latch */
  #endif
#else
  #if NEOC_USE_DMA
    sem_acquire_blocking(&reset_delay_complete_sem); /* get semaphore */
    dma_channel_set_read_addr(DMA_CHANNEL, (void*)address, true); /* trigger DMA transfer */
  #else
    for(int i=0; i<NEOC_NOF_PIXEL; i++) { /* without DMA: writing one after each other */
      put_pixel_wrgb(NEO_GetPixel32bitForPIO(NEOC_LANE_START, i));
    }
    vTaskDelay(pdMS_TO_TICKS(10)); /* latch */
  #endif
#endif
  return 0; /* ok */
}

void WS2812_Init(void) {
  PIO pio = pio0; /* the PIO used. \todo: find free PIO */
  sm = 0; /* could be local? */
#if WS2812_USE_MULTIPLE_LANES
  uint offset = pio_add_program(pio, &ws2812_parallel_program);
  ws2812_parallel_program_init(pio, sm, offset, NEOC_PIN_START, NEOC_NOF_LANES, 800000);
#else /* single lane */
  uint offset = pio_add_program(pio, &ws2812_program);
  ws2812_program_init(pio, sm, offset, NEOC_PIN_START, 800000, NEOC_NOF_COLORS==4);
#endif
#if NEOC_USE_DMA
  sem_init(&reset_delay_complete_sem, 1, 1); /* semaphore initially posted so we don't block first time */
  dma_init(pio, sm);
#endif
}

#endif /* PL_CONFIG_USE_NEO_PIXEL_HW */
