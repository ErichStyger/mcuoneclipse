/*
 * Printer.c
 *
 *  Created on: Mar 9, 2014
 *      Author: tastyger
 */
#include "AS1.h"
#include "WAIT1.h"

static void WriteChar(uint8_t ch) {
  AS1_SendChar(ch);
  WAIT1_Waitms(50);
}

static void WriteString(uint8_t *str) {
  while(*str!='\0') {
    WriteChar(*str);
    str++;
  }
}

/*!
 * \brief Feeds by the specified number of lines
 * \param lines Number of lines
 */
static void Feed(uint8_t lines) {
  while(lines>0) {
    WriteChar('\n');
  }
}

static void Test(void) {
  //Feed(1);
  WriteString((uint8_t*)"Hello World from the FRDM-KL25Z!\n");
  WAIT1_Waitms(500);
}


void PRNT_Init(void) {
  Test();
  for(;;);
}
