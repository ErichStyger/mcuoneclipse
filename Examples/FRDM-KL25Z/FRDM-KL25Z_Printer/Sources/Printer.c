/*
 * Printer.c
 *
 *  Created on: Mar 9, 2014
 *      Author: tastyger
 */
#include "Printer.h"
#include "AS1.h"
#include "WAIT1.h"

#define PRNT_WAIT_TIME_MS  50

/*!
 * \brief Writes a single character or byte to the printer.
 * \param ch Byte to write to the printer.
 */
void PRNT_WriteChar(uint8_t ch) {
  AS1_SendChar(ch);
  WAIT1_Waitms(PRNT_WAIT_TIME_MS); /* we have no flow control, so doing busy waiting here */
}

/*!
 * \brief Writes a string to the printer.
 * \param str String to print, zero byte terminated.
 */
void PRNT_WriteString(uint8_t *str) {
  while(*str!='\0') {
    PRNT_WriteChar(*str);
    str++;
  }
}

/*!
 * \brief Feeds by the specified number of lines.
 * \param lines Number of lines.
 */
void PRNT_Feed(uint8_t lines) {
  while(lines>0) {
    PRNT_WriteChar('\n');
  }
}

static void Test(void) {
  PRNT_WriteString((uint8_t*)"Hello World from the FRDM-KL25Z!\n");
  PRNT_Feed(1);
}

void PRNT_Init(void) {
  Test();
  for(;;);
}
