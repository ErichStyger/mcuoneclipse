/*
 * Kinetis.c
 *
 *  Created on: 23.07.2016
 *      Author: Erich Styger Local
 */

#include "Kinetis.h"
#include "CE.h"
#include "SS.h"
#include "WAIT1.h"
#include "SM1.h"
#include "EInt1.h"
#include <stdlib.h>

static uint32_t timer1msCounter = 0;

static void Error(void) {
  for(;;) {
    /* generic error */
  }
}

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
  /* configure the given pin for the mode indicated */
   if(mode==INPUT) {
    if (pin==KINETIS_CE) {
      CE_SetDir(FALSE);
    } else if (pin==KINETIS_SS) {
      SS_SetDir(FALSE);
    } else if (pin==KINETIS_ISR1) {
      /* nothing needed */
    } else {
      Error();
    }
  } else if (mode==OUTPUT) {
    if (pin==KINETIS_CE) {
      CE_SetDir(TRUE);
    } else if (pin==KINETIS_SS) {
      SS_SetDir(TRUE);
    } else if (pin==KINETIS_ISR1) {
      /* nothing needed */
    } else {
      Error();
    }
  } else {
    Error();
  }
}

void digitalWrite(GPIO_Pin pin, uint8_t level) {
  if (pin==KINETIS_CE) { /* SPI Slave Select Pin */
    CE_PutVal(level);
  } else if (pin==KINETIS_SS) {
    SS_PutVal(level);
  } else {
    Error();
  }
}

#if 0 /* not used */
uint8_t digitalRead(GPIO_Pin pin) {
  if (pin==KINETIS_CE) {
    return CE_GetVal();
  } else if (pin==KINETIS_SS) {
    return SS_GetVal();
  } else {
    Error();
  }
  return 0;
}
#endif

/*  milliseconds since process start */
unsigned long millis(void) {
  return timer1msCounter;
}

static void (*isr1)(void) = NULL;
void KINETIS_OnInterrupt1(void) {
  isr1();
}

void attachInterrupt(uint8_t interruptNumber, void (*isr)(void), INTERRUPT_Trigger trigger) {
  /* \todo */
  if (interruptNumber==KINETIS_ISR1) {
    isr1 = isr;
    if (trigger==RISING) {
      EInt1_SetEdge(1);
    } else if (trigger==FALLING) {
      EInt1_SetEdge(0);
    } else {
      Error();
    }
  } else {
    Error();
  }
}

void *memcpy_P(void *dst, const void *src, size_t srcSize) {
  return memcpy(dst, src, srcSize);
}

void delay(uint32_t ms) {
  WAIT1_Waitms(ms);
}

int random(int from, int to) {
  int val;

  val = rand();
  val = from + (val%(to-from+1));
  return val;
}


