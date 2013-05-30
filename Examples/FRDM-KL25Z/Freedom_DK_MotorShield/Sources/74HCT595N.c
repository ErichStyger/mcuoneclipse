/*
 * 74HCT595N.c
 *
 *  Created on: May 27, 2013
 *      Author: tastyger
 */

#include "Platform.h"

/*!
 * D12, DIR_LATCH, pin 12: STCP, Storage register clock input
 * D11, PWM2A, IC1 PWM
 * D10, PWM1B, Servo1
 * D09, PWM1A, Servo2
 * D08, DIR_SER, pin 14: DS, Serial Data Input
 * D07, DIR_EN,  pin 13: OE, Output Enable, low Active
 * D06, PWM0A, IC2 PWM
 * D05, PWM0B, IC2 PWM
 * D04, DIR_CLK, pin 11: SHCP, Shift register clock input
 * D03, PWM2B, IC1 PWM
 */

#include "DIR_LATCH.h" /* STCP, Storage register clock input. A pulse on this pin latches the data to the output pins */
#include "DIR_SER.h" /*  DS, Serial Data Input. This pin provides the serial data */
#include "DIR_CLK.h" /* SHCP, Shift register clock input. This is the clock pin to the device. */
#include "DIR_EN.h" /* OE, Output Enable, low active. If high, the device output pins are in Z-state (OFF) */
#include "WAIT1.h"

/* configures which device is used, as their timing is little bit different */
#define DEVICE_74HC595    1
#define DEVICE_74HCT595   0

#if DEVICE_74HC595
  #define STCP_LATCH_DELAY_NS  19
  #define SHCP_CLOCK_DELAY_NS  19
#else /* DEVICE_74HCT595 */
  #define STCP_LATCH_DELAY_NS  16
  #define SHCP_CLOCK_DELAY_NS  16
#endif

void HCT_Latch(void) {
  /* send a latch pulse to show the data on the output pins */
  DIR_LATCH_SetVal(); /* set latch to high */
#if STCP_LATCH_DELAY_NS != 0
  WAIT1_Waitns(STCP_LATCH_DELAY_NS); /* wait according to data sheet */
#endif
  DIR_LATCH_ClrVal(); /* set latch to low */
#if STCP_LATCH_DELAY_NS != 0
  WAIT1_Waitns(STCP_LATCH_DELAY_NS); /* wait according to data sheet */
#endif
}
/*!
 * \brief Shift a byte to the shift register. The most significant bit will be on output pin 0. Use Latch() to show the data on the output pins.
 * \param val 8bit value to be shifted
 */
void HCT_ShiftByte(uint8_t val) {
  /* see http://www.protostack.com/blog/2010/05/introduction-to-74hc595-shift-register-controlling-16-leds/ */
  int i;

  /* precondition: latch pin, data pin and clock pin are all low */
  for(i=0;i<8;i++) {
    /* put data bit */
    if (val&1) { /* LSB bit first */
      DIR_SER_SetVal();
    } else {
      DIR_SER_ClrVal();
    }
#if SHCP_CLOCK_DELAY_NS != 0
    WAIT1_Waitns(SHCP_CLOCK_DELAY_NS); /* wait according to data sheet */
#endif
    DIR_CLK_SetVal(); /* CLK high: data gets transfered into memory */
#if SHCP_CLOCK_DELAY_NS != 0
    WAIT1_Waitns(SHCP_CLOCK_DELAY_NS); /* wait according to data sheet */
#endif
    DIR_SER_ClrVal(); /* data line low */
#if SHCP_CLOCK_DELAY_NS != 0
    WAIT1_Waitns(SHCP_CLOCK_DELAY_NS); /* wait according to data sheet */
#endif
    DIR_CLK_ClrVal(); /* CLK high: data gets transfered into memory */
    val >>= 1; /* next bit */
  }
}

void HCT_Enable(void) {
  DIR_EN_ClrVal(); /* enable device */
}

void HCT_Disable(void) {
  DIR_EN_SetVal(); /* disable device */
}

void HCT_Init(void) {
  /* all pins low */
  DIR_LATCH_ClrVal();
  DIR_SER_ClrVal();
  DIR_CLK_ClrVal();
  DIR_EN_ClrVal(); /* device enabled by default */
}




