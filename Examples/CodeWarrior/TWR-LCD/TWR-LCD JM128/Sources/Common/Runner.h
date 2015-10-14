/** ###################################################################
**     Filename  : Motor.h
**     Project   : Tower_LCD
**     Processor : MCF51CN128CLK
**     Compiler  : CodeWarrior ColdFireV1 C Compiler
**     Date/Time : 15.01.2010, 18:32
**     Contents  :
**         User source code
**
** ###################################################################*/

#ifndef __Runner_H
#define __Runner_H

#include "platform.h"

#if PL_HAS_RUNNER

#include "UI1.h"

/* descriptor for our window */
#define RUNNER_DISPLAY_TEXT_SIZE 450
typedef struct {
  UI1_Screen screen;
  UI1_Window window;
  UI1_Header header;
  UI1_Icon iconClose;
  UI1_Icon iconDelLast;
  UI1_Text runnerTxt;
  char runnerTxtBuf[RUNNER_DISPLAY_TEXT_SIZE];
} RUNNER_WindowDesc;

void RUNNER_GetCmdString(char *buf, size_t bufSize);

void RUNNER_StartTask(RUNNER_WindowDesc *desc);

#endif /* PL_HAS_RUNNER */


#endif /* __Runner_H */

