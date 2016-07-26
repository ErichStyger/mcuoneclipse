/*
 * Kinetis.c
 *
 *  Created on: 23.07.2016
 *      Author: Erich Styger Local
 */

#include "Kinetis.h"
#include "nRFCE.h"
#include "nRFCSN.h"
#include "WAIT1.h"
#include "SM1.h"
#include <stdlib.h>

static uint32_t timer1msCounter = 0;

void On1msTimerInterrrupt(void) {
  timer1msCounter++;
}

uint8_t HardwareSPI::transfer(uint8_t val) {
  uint8_t ch;

  while(SM1_GetCharsInTxBuf()!=0) {} /* wait until tx is empty */
  while(SM1_SendChar(val)!=ERR_OK) {} /* send character */
  while(SM1_GetCharsInTxBuf()!=0) {} /* wait until data has been sent */
  while(SM1_GetCharsInRxBuf()==0) {} /* wait until we receive data */
  while(SM1_RecvChar(&ch)!=ERR_OK) {} /* get data */
  return ch;
}

void HardwareSPI::end(void) {
  /* nothing */
}

void pinMode(GPIO_Pin pin, GPIO_Mode mode) {
}

void digitalWrite(GPIO_Pin pin, uint8_t level) {
  if (pin==KINETIS_CE) {
    nRFCE_PutVal(level);
  } else if (pin==KINETIS_SS) {
    nRFCSN_PutVal(level);
  } else {
    for(;;);/* error */
  }
}

#if 0 /* not used */
uint8_t digitalRead(GPIO_Pin pin) {
  if (pin==KINETIS_CE) {
    return nRFCE_GetVal();
  } else if (pin==KINETIS_SS) {
    return nRFCSN_GetVal();
  } else {
    for(;;);/* error */
  }
  return 0;
}
#endif

/*  milliseconds since process start */
unsigned long millis(void) {
  return timer1msCounter;
}

#if 0 /* not used */
void attachInterrupt(uint8_t interruptNumber, void (*isr0)(void), INTERRUPT_Trigger trigger) {
}
#endif

//void *memcpy_P(void *dst, const void *src, size_t srcSize) {
//  return memcpy(dst, src, srcSize);
//}

void delay(uint32_t ms) {
  WAIT1_Waitms(ms);
}

int random(int from, int to) {
  int val;

  val = rand();
  val = from + (val%(to-from+1));
  return val;
}


