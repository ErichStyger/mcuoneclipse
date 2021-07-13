/*
  ws2812b.c

  PLU will be configured as SPI client. 
  SPI clock should 800kHz: SPI clock div for the main clk can be 24 or 23
  
  PLU configuration:
    SPI Clock: PIO0_9;
    SPI MOSI: PIO0_11;
*/

#include "platform.h"
#include "ws2812b.h"
#include "LPC8xx.h"
#include "syscon.h"
#include "spi.h"
#include "McuWait.h"
#include "plu_setup.h"

static void spi_init(void) {
  Enable_Periph_Clock(CLK_SPI0);
  LPC_SYSCON->SPI0CLKSEL = FCLKSEL_MAIN_CLK;	
  LPC_SPI0->DIV = 24;	/* 22 still seems to work */
  LPC_SPI0->CFG = SPI_CFG_ENABLE | SPI_CFG_MASTER;
}

void WS2812B_spi_out(uint8_t *data, size_t cnt) {
  LPC_SPI0->TXCTL = 
      SPI_CTL_RXIGNORE | 		/* do not read data from MISO */
      SPI_CTL_LEN(8) | 			/* send 8 bits */
      SPI_TXDATCTL_SSELN(3); 	/* do not use any slave select */
  for(int i=0; i<cnt; i++) {
    /* wait until the tx register can accept further data */
    while( (LPC_SPI0->STAT & SPI_STAT_TXRDY) == 0 ) {}
    /* ensure, that the SCK goes to low after the byte transfer: */
    /* Set the EOT flag at the end of the transfer */
    if (i+1 == cnt) {
      LPC_SPI0->TXCTL |= SPI_CTL_EOT;
    }
    LPC_SPI0->TXDAT = data[i]; /* transfer one byte via SPI */
  }
}

void WS2812B_SendPixels(uint8_t *data, size_t cnt) {
  WS2812B_spi_out(data, cnt);
  /* LPC804 has might have up to two bytes in the queue, wait for their transmission */
  McuWait_Waitus(24+24);
  /* write the new values into the LEDs */
  McuWait_Waitus(50);
}

void WS2812B_Init(void) {
  PLU_setup(); /*  will enable SWM clock */
  spi_init();
}
