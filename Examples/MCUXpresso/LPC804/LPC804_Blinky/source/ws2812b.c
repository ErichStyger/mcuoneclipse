/*
 * Copyright (c) 2021, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#include "ws2812b.h"
#include "fsl_spi.h"
#include "McuWait.h"
#include "plu_setup.h"

static void SPI_Init(void) {
  CLOCK_EnableClock(kCLOCK_Spi0); /* enable peripheral clock */
  SYSCON->SPI0CLKSEL = SYSCON_SPI0CLKSEL_SEL(1); /* use main clock */
  SPI0->DIV = 24; /* divider for reaching 500'000 baud at 15 MHz clock rate */
  SPI0->CFG = SPI_CFG_ENABLE_MASK | SPI_CFG_MASTER_MASK;
}

void WS2812B_spi_out(uint8_t *data, size_t cnt) {
  SPI0->TXCTL =
      SPI_TXDATCTL_RXIGNORE_MASK |    /* do not read data from MISO */
      SPI_TXDATCTL_LEN(7) |           /* send 8 bits */
      SPI_TXDATCTL_TXSSEL0_N(3);      /* do not use any slave select */
  for(int i=0; i<cnt; i++) {
    while( (SPI0->STAT & SPI_STAT_TXRDY_MASK) == 0 ) {
      /* block until there is space in the TX register for receiving the data */
    }
    if (i+1 == cnt) {
      /* need to make sure that the CLK line goes LOW after sending: send EOT */
      SPI0->TXCTL |= SPI_TXCTL_EOT(1);
    }
    SPI0->TXDAT = data[i]; /* send one byte  */
  }
}

void WS2812B_SendPixels(uint8_t *data, size_t cnt) {
  WS2812B_spi_out(data, cnt);
  McuWait_Waitus(2*24); /* LPC804 has might have up to two bytes in the queue, wait for their transmission */
  McuWait_Waitus(50); /* write the new values into the LEDs: signal low for 50us to latch the data */
}

void WS2812B_Init(void) {
  SPI_Init(); /* initialize and enable SPI */
  PLU_setup(); /*  initialize the PLU and configure clocks */
}
