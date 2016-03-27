/*
 * Application.h
 *
 *  Created on: 27.03.2016
 *      Author: Erich Styger
 */
#include <stdint.h> /* standard int types */
#include "WS2812.h"

/* This define calculates the needed number of 32bit words needed. */
#define	ALIGN_32BIT_WORDS(x)	    ((3*(x)+3)/4)

#define	STRIP_LED_CNT		    4 /* number of WS2812B LEDs */
static uint32_t led_data[ALIGN_32BIT_WORDS(STRIP_LED_CNT+1)]; /* plus one dummy LED at the end to drive signal low */

static void SetLEDColor(uint8_t led, uint8_t red, uint8_t green, uint8_t blue) {
  ws2812_control *p = (ws2812_control*)led_data;

  if (led<=STRIP_LED_CNT) { /* within index */
    p[led].red    = red;
    p[led].green  = green;
    p[led].blue   = blue;
  }
}

static void delay(void) {
  volatile uint32_t val = 0x1000;

  while(val>0) {
    __asm("nop");
    val--;
  }
}

void APP_Run(void) {
  int i;

	for(i=0; i<STRIP_LED_CNT; i++) {
	  SetLEDColor(i, 0, 0, 0); /* init */
	}
	WS2812_Init();
	WS2812_PinSelect();
	i = 0;
	for(;;) {
    if (i==0) {
      SetLEDColor(0, 0x20, 0x00, 0x00); /* red */
      SetLEDColor(1, 0x00, 0x20, 0x00); /* green */
      SetLEDColor(2, 0x00, 0x00, 0x20); /* blue */
      SetLEDColor(3, 0x1F, 0x00, 0x1F); /* purple */
      i++;
    } else if (i==100) {
      SetLEDColor(0, 0x20, 0x20, 0x20); /* white */
      SetLEDColor(1, 0x20, 0x00, 0x20); /* red */
      SetLEDColor(2, 0x20, 0x20, 0x00); /* orange */
      SetLEDColor(3, 0x00, 0x00, 0x20); /* blue */
      i++;
    } else if (i==200) {
      i = 0;
    } else {
      i++;
    }
    WS2812_OutputDataDMA(led_data, sizeof(led_data)/sizeof(int32_t));
		delay();
	} /* for */
}
